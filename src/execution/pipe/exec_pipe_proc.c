/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_proc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:39 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/23 13:13:10 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	close_unused_fds(int control_fd, int pipe_fd[2])
{
	if (control_fd != -1)
		close(control_fd);
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

static void	exec_child_proc(t_shell *shell, t_command *cmd, int std_in, \
	int std_out)
{
	char	*path;

	if (is_builtin(cmd))
	{
		if (exec_builtin(shell, cmd, std_in, std_out) != 0)
			free_all(shell, EXIT_FAILURE);
		free_all(shell, EXIT_SUCCESS);
	}
	if (!shell->cmd->command_name)
		free_all(shell, EXIT_SUCCESS);
	path = get_path(shell, cmd);
	check_error(path, shell->cmd, shell);
	execve(path, cmd->args, shell->new_envp);
	handle_error(shell, cmd);
}

void	child_proc(t_shell *shell, t_command *cmd, int control_fd, int fd[2])
{
	child_signals();
	if (control_fd != -1)
	{
		if (dup2(control_fd, STDIN_FILENO) == -1)
			perror("dup2 control_fd");
	}
	if (cmd->next && dup2(fd[1], STDOUT_FILENO) == -1)
		perror("dup2 pipe write");
	if (cmd->redirs && definy_fd(cmd))
	{
		close_unused_fds(control_fd, fd);
		free_all(shell, EXIT_FAILURE);
	}
	close_unused_fds(control_fd, fd);
	exec_child_proc(shell, cmd, control_fd, fd[1]);
}

void	parent_proc(t_command *cmd, int *control_fd, int fd[2])
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
