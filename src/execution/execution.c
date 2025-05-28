/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:32:49 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/28 17:29:08 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// if is builtin and no error ocurred, it returns 0, if not builtin 1
// if no command name -1.
static int	is_builtin(t_shell *shell)
{
	if (!shell->cmd->command_name)
		return (-1);
	if (ft_strcmp(shell->cmd->command_name, "echo") == 0)
		return (exec_echo_builtin(shell));
	else if (ft_strcmp(shell->cmd->command_name, "cd") == 0)
		return (exec_cd_builtin(shell));
	else if (ft_strcmp(shell->cmd->command_name, "pwd") == 0)
		return (pwd_builtin());
	else if (ft_strcmp(shell->cmd->command_name, "export") == 0)
		return (exec_export_builtin(shell));
	else if (ft_strcmp(shell->cmd->command_name, "unset") == 0)
		return (exec_unset_builtin(shell));	
	else if (ft_strcmp(shell->cmd->command_name, "env") == 0)
	 	return (exec_env_builtin(shell));
	// else if (ft_strcmp(shell->cmd->command_name, "exit") == 0)
	// 	return (exec_exit_builtin());
	return (1);
}

// REVER SOH MONTEI COMO "MODELO"
void	exec_cmd(t_shell *shell)
{
	if (is_builtin(shell) == 0)
	{
		//printf("builtin executed\n");
		return ;
	}	
	// else if (has_pipe(cmd))
	// 	exec_pipeline(cmd);
	// else
	else if (shell->cmd->next)
		exec_pipeline(shell->cmd);
	else
		{
			//printf("external command executed\n");
			exec_external_cmd(shell->cmd);	
		}
		
}
