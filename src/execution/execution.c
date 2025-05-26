/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:32:49 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/26 18:40:02 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// REVER SOH MONTEI COMO "MODELO"
// lembrar the atualizar envp depois de export, unset e cd.
// talvez dentro de is_builtin.
void	exec_cmd(t_shell *shell)
{
	if (is_builtin(shell->cmd, shell->vars, shell->new_envp) == 0)
		return ;
	// else if (has_pipe(cmd))
	// 	exec_pipeline(cmd);
	// else
	else if (shell->cmd->next)
		exec_pipeline(shell->cmd);
	else
		exec_external_cmd(shell->cmd);
}

// if is builtin and no error ocurred, it returns 0, else 1.
int	is_builtin(t_command *cmd, t_var **vars, t_shell *shell)
{
	// if (ft_strcmp(cmd->command_name, "echo") == 0)
	// 	return (exec_echo_builtin());
	if (ft_strcmp(cmd->command_name, "cd") == 0)
		return (exec_cd_builtin());
	else if (ft_strcmp(cmd->command_name, "pwd") == 0)
		return (pwd_builtin());
	else if (ft_strcmp(cmd->command_name, "export") == 0)
		return (exec_export_builtin());
	else if (ft_strcmp(cmd->command_name, "unset") == 0)
		return (exec_unset_builtin());	
	// else if (ft_strcmp(cmd->command_name, "env") == 0)
	// 	return (exec_env_builtin());
	// else if (ft_strcmp(cmd->command_name, "exit") == 0)
	// 	return (exec_exit_builtin());
	return (1);
}
