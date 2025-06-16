/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:32:49 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/04 16:16:12 by jcosta-b         ###   ########.fr       */
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

int	exec_builtin(t_shell *shell, t_command *cmd, int std_in, int std_out)
{
	int	control;

	control = 0;
	if (ft_strcmp(cmd->command_name, "echo") == 0)
		control = exec_echo_builtin(cmd);
	else if (ft_strcmp(cmd->command_name, "cd") == 0)
		control = exec_cd_builtin(shell, cmd);
	else if (ft_strcmp(cmd->command_name, "pwd") == 0)
		control = pwd_builtin();
	else if (ft_strcmp(cmd->command_name, "export") == 0)
		control = exec_export_builtin(shell, cmd);
	else if (ft_strcmp(cmd->command_name, "unset") == 0)
		control = exec_unset_builtin(shell, cmd);
	else if (ft_strcmp(cmd->command_name, "env") == 0)
		control = exec_env_builtin(shell, cmd);
	else
		control = exec_exit_builtin(shell, cmd, std_in, std_out);
	return (control);
}

void	dup2_and_close(int std_in, int std_out)
{
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	if (std_in != -1)
		close(std_in);
	if (std_in != -1)
		close(std_out);
}

int	handle_builtin(t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	control;

	control = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (1);
	if (shell->cmd->redirs)
	{
		if (definy_fd(shell->cmd))
		{
			dup2_and_close(saved_stdin, saved_stdout);
			return (1);
		}
	}
	control = exec_builtin(shell, shell->cmd, saved_stdin, saved_stdout);
	dup2_and_close(saved_stdin, saved_stdout);
	if (control != 0)
			return (1);
	return (0);
}
