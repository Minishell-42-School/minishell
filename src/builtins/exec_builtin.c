/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:32:49 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/03 13:53:03 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_command *cmd)
{
	char	*cmd_name;

	cmd_name = cmd->command_name;
	if (!ft_strcmp(cmd_name, "echo") || !ft_strcmp(cmd_name, "cd") || \
		!ft_strcmp(cmd_name, "pwd") || !ft_strcmp(cmd_name, "export") || \
		!ft_strcmp(cmd_name, "unset") || !ft_strcmp(cmd_name, "env") || \
		!ft_strcmp(cmd_name, "exit"))
		return (1);
	return (0);
}

void	exec_builtin(t_shell *shell)
{
	if (ft_strcmp(shell->cmd->command_name, "echo") == 0)
		exec_echo_builtin(shell);
	else if (ft_strcmp(shell->cmd->command_name, "cd") == 0)
		exec_cd_builtin(shell);
	else if (ft_strcmp(shell->cmd->command_name, "pwd") == 0)
		pwd_builtin();
	else if (ft_strcmp(shell->cmd->command_name, "export") == 0)
		exec_export_builtin(shell);
	else if (ft_strcmp(shell->cmd->command_name, "unset") == 0)
		exec_unset_builtin(shell);
	else if (ft_strcmp(shell->cmd->command_name, "env") == 0)
		exec_env_builtin(shell);
	else
		exec_exit_builtin(shell);
}

int	handle_builtin(t_shell *shell)
{
	int		saved_stdin;
	int		saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (shell->cmd->redirs)
	{
		if (definy_fd(shell->cmd))
			return (1);
	}
	exec_builtin(shell);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (0);
}
