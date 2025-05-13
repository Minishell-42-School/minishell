/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/13 18:17:56 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	child_proc(t_command *cmd)
{
	int	fd;
	char	*path;

	// if (!cmd->redirs->next) // Apenas 1 redir

	printf("REDIR %d\n", cmd->redirs->type);
	if (cmd->redirs->type == R_OUT) // >
		fd = open(cmd->redirs->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (cmd->redirs->type == R_APPEND) // >>
		fd = open(cmd->redirs->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (cmd->redirs->type == R_IN) // <
		fd = open(cmd->redirs->filename, O_RDONLY);
	else
		fd = -1;

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
