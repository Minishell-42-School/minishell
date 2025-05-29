/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/29 12:46:03 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_out(t_redirections *redir)
{
	int	fd;

	if (redir->type == R_OUT)
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error for open the file");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("Error - dup");
		close(fd);
		return ;
	}
	close(fd);
}

void	handle_in(t_redirections *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error for open the file");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("Error - dup");
		close(fd);
		return ;
	}
	close(fd);
}

void	handle_creat(t_redirections *redir)
{
	int	fd;

	fd = open(redir->filename, O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Error for open the file");
		return ;
	}
	close(fd);
}

void	definy_fd(t_command *cmd)
{
	t_redirections	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		while (redir->next && ((redir->type == R_IN && \
			redir->next->type == R_IN) || \
			((redir->type == R_OUT || redir->type == R_APPEND) && \
			(redir->next->type == R_OUT || redir->next->type == R_APPEND))))
		{
			handle_creat(redir);
			redir = redir->next;
		}
		if (redir->type == R_OUT || redir->type == R_APPEND)
			handle_out(redir);
		else if (redir->type == R_IN)
			handle_in(redir);
		else
			handle_heredoc(redir);
		redir = redir->next;
	}
}

// static void	child_proc(t_command *cmd)
// {
// 	char	*path;

// 	signal(SIGINT, SIG_DFL);
// 	definy_fd(cmd);
// 	path = get_path(cmd);
// 	if (!path)
// 	{
// 		perror("get_path");
// 		exit(EXIT_FAILURE);
// 	}
// 	execve(path, cmd->args, NULL);
// 	perror("execve");
// 	exit(EXIT_FAILURE);
// }

// void	exec_redir(t_command *cmd)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		return ((void)printf("Error at fork\n"));
// 	if (pid == 0)
// 		child_proc(cmd);
// 	else
// 		wait(NULL);
// }
