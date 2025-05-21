/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:32:49 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/13 18:08:38 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// REVER SOH MONTEI COMO "MODELO"
// void	exec_cmd(t_command *cmd)
// {
// 	// if (is_builtin(cmd))
// 	// 	exec_builtin(cmd);
// 	// else if (has_pipe(cmd))
// 	// 	exec_pipeline(cmd);
// 	// else
// 	if (cmd->redirs)
// 		exec_redir(cmd);
// 	// if (cmd->next)
// 	// 	exec_pipeline(cmd);
// 	else
// 		exec_external_cmd(cmd);
// }

void	exec_cmd(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->next)
	{
		exec_pipeline(cmd);
		return ;
	}
	// if (is_builtin(cmd) && !cmd->redirs)
	// {
	// 	exec_builtin(cmd);
	// 	return ;
	// }
	if (cmd->redirs)
	{
		exec_redir(cmd);
		return ;
	}
	exec_external_cmd(cmd);
}
