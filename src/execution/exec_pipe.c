/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:39 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/04 16:25:54 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_child_proc(t_shell *shell, t_command *cmd)
{
	char	*path;

	if (is_builtin(cmd))
	{
		if (exec_builtin(shell, cmd) != 0)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	path = get_path(shell, cmd);
	check_error(path, shell->cmd);
	execve(path, cmd->args, shell->new_envp);
	handle_error(cmd);
}

static void	child_proc(t_shell *s, t_command *cmd, int control_fd, int fd[2])
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
		if (definy_fd(cmd))
			exit(EXIT_FAILURE);
	exec_child_proc(s, cmd);
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
		close(fd[0]);
}

static void	pipe_signal(t_shell *shell)
{
	int	status;

	ign_signals();
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			shell->last_status = WEXITSTATUS(status);
	}
	config_signals();
}

void	exec_pipe(t_shell *shell)
{
	int			fd[2];
	int			control_fd;
	pid_t		pid;
	t_command	*cmd;

	control_fd = -1;
	cmd = shell->cmd;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return ((void)perror("pipe"));
		pid = fork();
		if (pid == -1)
			return ((void)perror("fork"));
		if (pid == 0)
			child_proc(shell, cmd, control_fd, fd);
		else
		{
			parent_proc(cmd, &control_fd, fd);
			cmd = cmd->next;
		}
	}
	pipe_signal(shell);
}
