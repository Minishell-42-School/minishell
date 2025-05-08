/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:39 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/08 10:51:57 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_proc(t_command *cmd, int control_fd, int fd[2])
{
	char	*path;

	if (control_fd != -1)
	{
		dup2(control_fd, STDIN_FILENO);
		close(control_fd);
	}
	if (cmd->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	path = get_path(cmd);
	execve(path, cmd->args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	parent_proc(t_command *cmd, int *control_fd, int fd[2])
{
	if (*control_fd != -1)
		close(*control_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*control_fd = fd[0];
	}
}

void	exec_pipeline(t_command *cmd)
{
	int		fd[2];
	int		control_fd;
	pid_t	pid;

	control_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return ((void)printf("Error at pipe\n"));
		pid = fork();
		if (pid == -1)
			return ((void)printf("Error at fork\n"));
		if (pid == 0)
			child_proc(cmd, control_fd, fd);
		else
		{
			parent_proc(cmd, &control_fd, fd);
			cmd = cmd->next;
		}
	}
	while (wait(NULL) > 0);
}
