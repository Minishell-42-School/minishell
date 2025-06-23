/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:32:49 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/23 11:58:52 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_shell *shell)
{
	int	last_exit;

	last_exit = 0;
	if (shell->last_status)
		last_exit = shell->last_status;
	shell->last_status = 0;
	if (!shell->cmd)
		return ;
	verif_heredoc(shell, last_exit);
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
