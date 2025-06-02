/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:39 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/02 12:09:39 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_child_proc(t_command *cmd)
{
	char	*path;

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

static void	child_proc(t_command *cmd, int control_fd, int fd[2])
{
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
	if (cmd->redirs)
		definy_fd(cmd);
	exec_child_proc(cmd);
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
	else
	{
		close(fd[0]);
	}
}

void	pipe_signal(void)
{
	int	status;

	ign_signals();
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
	config_signals();
}

void	exec_pipe(t_command *cmd)
{
	int		fd[2];
	int		control_fd;
	pid_t	pid;

	control_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return ((void)perror("pipe"));
		pid = fork();
		if (pid == -1)
			return ((void)perror("fork"));
		if (pid == 0)
			child_proc(cmd, control_fd, fd);
		else
		{
			parent_proc(cmd, &control_fd, fd);
			cmd = cmd->next;
		}
	}
	pipe_signal();
}
