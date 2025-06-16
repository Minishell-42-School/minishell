/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:55:17 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/16 16:21:59 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_child_proc(t_shell *shell)
{
	char	*path;

	if (shell->cmd->redirs)
	{
		if (definy_fd(shell->cmd))
			free_all(shell, EXIT_FAILURE);
	}
	if (shell->last_status == 130)
		free_all(shell, 130);
	path = get_path(shell, shell->cmd);
	check_error(path, shell->cmd, shell);
	if (execve(path, shell->cmd->args, shell->new_envp) == -1)
		handle_error(shell, shell->cmd);
	free_all(shell, EXIT_SUCCESS);
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
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->term_backup);
}

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
