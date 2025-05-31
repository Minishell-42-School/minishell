/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:39 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/29 17:01:29 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	definy_redir_fd(t_command *cmd)
{
	t_redirections	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_DELIMITER)
		{
			r = r->next;
			continue ;
		}
		while (r->next && ((r->type == R_IN && r->next->type == R_IN) || \
				((r->type == R_OUT || r->type == R_APPEND) && \
				(r->next->type == R_OUT || r->next->type == R_APPEND))))
		{
			handle_creat(r);
			r = r->next;
		}
		if (r->type == R_OUT || r->type == R_APPEND)
			handle_out(r);
		else if (r->type == R_IN)
			handle_in(r);
		else
			continue ;
		r = r->next;
	}
}

// void	verif_heredoc(t_redirections *redir, int *hdoc_control)
// {
// 	while (redir)
// 	{
// 		if (redir->type == R_DELIMITER)
// 		{
// 			handle_heredoc(redir);
// 			*hdoc_control = 1;
// 			return ;
// 		}
// 		redir = redir->next;
// 	}
// }

void	close_files(t_command *cmd)
{
	t_redirections	*redir;

	while (cmd)
	{
		if (cmd->redirs)
		{
			redir = cmd->redirs;
			while (redir)
			{
				if (redir->type == R_OUT || redir->type == R_APPEND)
					unlink(redir->filename);
				redir = redir->next;
			}
		}
		cmd = cmd->next;
	}
	free_command_list(cmd);
}

// void	pipe_signal(t_command *cmd, pid_t pid)
// {
// 	int	status;

// 	ign_signals();
// 	while (waitpid(pid, &status, 0) > 0)
// 	{
// 		config_signals();
// 		if (WIFSIGNALED(status))
// 			g_exit_status = 128 + WTERMSIG(status);
// 		else
// 			g_exit_status = WEXITSTATUS(status);
// 		if (g_exit_status == 130)
// 			close_files(cmd);
// 	}
// }
