/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:32:49 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/19 11:42:43 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// REVER SOH MONTEI COMO "MODELO"
void	exec_cmd(t_command *cmd)
{
	// if (is_builtin(cmd))
	// 	exec_builtin(cmd);
	// else if (has_pipe(cmd))
	// 	exec_pipeline(cmd);
	// else
	if (cmd->next)
		exec_pipeline(cmd);
	else
		exec_external_cmd(cmd);
}
