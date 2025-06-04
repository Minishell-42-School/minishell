/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:32:49 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/03 13:52:43 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_shell *shell)
{
	shell->last_status = 0;
	if (!shell->cmd)
		return ;
	verif_heredoc(shell);
	if (shell->last_status == 130)
		return ;
	if (shell->cmd->next)
	{
		exec_pipe(shell);
		return ;
	}
	if (is_builtin(shell->cmd))
	{
		if (handle_builtin(shell))
			shell->last_status = 1;
		return ;
	}
	exec_simple_cmd(shell);
}
