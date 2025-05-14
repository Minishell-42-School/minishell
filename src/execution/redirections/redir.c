/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/14 12:56:25 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_redirs(t_redirections *redir_lst)
{
	int	times;

	times = 1;
	if (redir_lst->type == R_OUT || redir_lst->type == R_APPEND)
	{
		while (redir_lst->next && (redir_lst->next->type == R_OUT || \
				redir_lst->next->type == R_APPEND))
		{
			times++;
			redir_lst = redir_lst->next;
		}
	}
	else if (redir_lst->type == R_IN)
	{
		while (redir_lst->next && redir_lst->type == R_IN)
		{
			times++;
			redir_lst = redir_lst->next;
		}
	}
	else
		times = 0;
	return (times);
}

static void	child_proc(t_command *cmd)
{
	int	fd;
	char	*path;
	int	times;

	times = count_redirs(cmd->redirs);
	printf("times = %d\n", times);
	if (times == 0) // <<
		fd = -1;
	else if (times > 1)
	{
		while (times > 1)
		{
			if (cmd->redirs->type == R_OUT) // >
				fd = open(cmd->redirs->filename, O_CREAT, 0644);
			else if (cmd->redirs->type == R_APPEND) // >>
				fd = open(cmd->redirs->filename, O_CREAT, 0644);
			else // if (cmd->redirs->type == R_IN) // <
				fd = open(cmd->redirs->filename, O_CREAT);
			close(fd);
			cmd->redirs = cmd->redirs->next;
			times--;
		}
	}
	if (times == 1) // Only one redir
	{
		if (cmd->redirs->type == R_OUT) // >
			fd = open(cmd->redirs->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (cmd->redirs->type == R_APPEND) // >>
			fd = open(cmd->redirs->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else // if (cmd->redirs->type == R_IN) // <
			fd = open(cmd->redirs->filename, O_RDONLY);
	}

	
	// if (cmd->redirs->type == R_OUT) // >
	// 	fd = open(cmd->redirs->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// else if (cmd->redirs->type == R_APPEND) // >>
	// 	fd = open(cmd->redirs->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	// else if (cmd->redirs->type == R_IN) // <
	// 	fd = open(cmd->redirs->filename, O_RDONLY);
	// else
	// 	fd = -1;

	if (fd == -1)
	{
		perror("Error for open the file");
		return ;
	}
	
	if (cmd->redirs->type == R_OUT || cmd->redirs->type == R_APPEND)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			printf("Error - dup");
			close(fd);
			return ;
		}
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			printf("Error - dup");
			close(fd);
			return ;
		}
	}
	close(fd);

	path = get_path(cmd);
	if (!path)
	{
		perror("get_path");
		exit(EXIT_FAILURE);
	}
	execve(path, cmd->args, NULL); 
	perror("execve");
	exit(EXIT_FAILURE);
}

void	exec_redir(t_command *cmd)
{
	pid_t	pid;
	// int		status;

	pid = fork();
	if (pid == -1)
		return ((void)printf("Error at fork\n"));
	if (pid == 0)
		child_proc(cmd);
	else
		wait(NULL);
}
