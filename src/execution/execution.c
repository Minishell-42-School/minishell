/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:32:49 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/02 12:27:34 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_command *cmd)
{
	g_exit_status = 0;
	if (!cmd)
		return ;
	verif_heredoc(cmd);
	if (g_exit_status == 130)
		return ;
	if (cmd->next)
	{
		exec_pipe(cmd);
		return ;
	}
	// if (is_builtin(cmd) && !cmd->redirs)
	// {
	// 	exec_builtin(cmd);
	// 	return ;
	// }
	// else
	exec_simple_cmd(cmd);
}
