/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:39 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/05 14:29:48 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	pipe_signal(t_shell *shell, pid_t last_pid)
{
	int		status;
	int		control;
	pid_t	wpid;

	ign_signals();
	control = 0;
	wpid = waitpid(-1, &status, 0);
	while (wpid > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				shell->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->last_status = 128 + WTERMSIG(status);
		}
		else if (WIFSIGNALED(status) && status == SIGINT && control == 0)
		{
			printf("\n");
			control = 1;
		}
		wpid = waitpid(-1, &status, 0);
	}
	config_signals();
}

static void	looping_pipe(t_shell *shell, t_command *cmd, pid_t *last_pid)
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
			child_proc(shell, cmd, control_fd, fd);
		else
		{
			if (!cmd->next)
				*last_pid = pid;
			parent_proc(cmd, &control_fd, fd);
			cmd = cmd->next;
		}
	}
  tcsetattr(STDIN_FILENO, TCSANOW, &shell->term_backup);
}

void	exec_pipe(t_shell *shell)
{
	pid_t		last_pid;
	t_command	*cmd;

	cmd = shell->cmd;
	last_pid = -1;
	looping_pipe(shell, cmd, &last_pid);
	pipe_signal(shell, last_pid);
}
