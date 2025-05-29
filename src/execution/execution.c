/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:32:49 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/22 17:18:09 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->next)
	{
		exec_pipe(cmd);
		return ;
	}
	else
	{
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
}
