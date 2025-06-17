/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:09:03 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/12 15:40:21 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirections	*assign_redir_type(t_parser_state *p_state,
	t_redirections *redir)
{
	t_token	*token;

	token = p_state->current;
	if (token->type == REDIR_IN)
		redir->type = R_IN;
	else if (token->type == REDIR_OUT)
		redir->type = R_OUT;
	else if (token->type == REDIR_HEREDOC)
		redir->type = R_HEREDOC;
	else if (token->type == REDIR_APPEND)
		redir->type = R_APPEND;
	else
		return (NULL);
	advance_token(p_state);
	return (redir);
}

void	link_redir(t_command *cmd, t_redirections *redir)
{
	t_redirections	*last;

	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
}

t_hdoc	assign_hdoc_expansion(t_token *token)
{
	if (token->hdoc == EXPAND_VAR)
		return (EXPAND);
	else
		return (NO_EXPAND);
}
