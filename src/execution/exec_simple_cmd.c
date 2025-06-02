/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:55:17 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/02 16:52:14 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_child_proc(t_shell *shell)
{
	char	*path;

	if (shell->cmd->redirs)
		definy_fd(shell->cmd);
	if (shell->last_status == 130)
		exit(130);
	path = get_path(shell->cmd);
	if (!path)
		exit(EXIT_FAILURE);
	if (execve(path, shell->cmd->args, shell->new_envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

static void	exec_parent_proc(t_shell *shell, pid_t pid)
{
	int	status;

	ign_signals();
	waitpid(pid, &status, 0);
	config_signals();
	if (WIFSIGNALED(status))
		shell->last_status = 128 + WTERMSIG(status);
	else
		shell->last_status = WEXITSTATUS(status);
}

// void	exec_simple_cmd(t_command *cmd)
void	exec_simple_cmd(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		exec_child_proc(shell);
	else
		exec_parent_proc(shell, pid);
}
