/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:32:49 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/02 13:47:55 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	exec_cmd(t_command *cmd)
// {
// 	g_exit_status = 0;
// 	if (!cmd)
// 		return ;
// 	verif_heredoc(cmd);
// 	if (g_exit_status == 130)
// 		return ;
// 	if (cmd->next)
// 	{
// 		exec_pipe(cmd);
// 		return ;
// 	}
// 	// if (is_builtin(cmd) && !cmd->redirs)
// 	// {
// 	// 	exec_builtin(cmd);
// 	// 	return ;
// 	// }
// 	// else
// 	exec_simple_cmd(cmd);

// }


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
	else if (ft_strcmp(shell->cmd->command_name, "exit") == 0)
		return (exec_exit_builtin(shell));
	return (1);
}

// REVER SOH MONTEI COMO "MODELO"
void	exec_cmd(t_shell *shell)
{
	// 	g_exit_status = 0;
	if (!shell->cmd)
		return ;
	verif_heredoc(shell->cmd);
	if (g_exit_status == 130)
		return ;
	if (shell->cmd->next)
	{
		exec_pipe(shell->cmd);
		return ;
	}
	if (is_builtin(shell) == 0)
	{
		//printf("builtin executed\n");
		return ;
	}	
	// else if (has_pipe(cmd))
	// 	exec_pipeline(cmd);
	// else
	else
	{
		//printf("external command executed\n");
		exec_external_cmd(shell->cmd);	
	}
}

// void	exec_cmd(t_command *cmd)
// {

// 	if (!cmd)
// 		return ;
// 	verif_heredoc(cmd);
// 	if (g_exit_status == 130)
// 		return ;
// 	if (cmd->next)
// 	{
// 		exec_pipe(cmd);
// 		return ;
// 	}
// 	// if (is_builtin(cmd) && !cmd->redirs)
// 	// {
// 	// 	exec_builtin(cmd);
// 	// 	return ;
// 	// }
// 	// else
// 	exec_simple_cmd(cmd);

// }
