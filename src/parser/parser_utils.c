/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:09:03 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/11 17:39:22 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//returns current token and advances state to the next
t_token	*advance_token(t_parser_state *p_state)
{
	t_token	*token;

	token = p_state->current;
	if (p_state->current != NULL)
		p_state->current = p_state->current->next;
	return (token);
}

t_command	*init_command_struct(t_shell *shell)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		perror("Malloc parser cmd failed");
		free_all(shell, EXIT_FAILURE);
	}
	cmd->command_name = NULL;
	cmd->args = NULL;
	cmd->args_count = 0;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	count_args(t_parser_state *p_state)
{
	t_parser_state	temp;
	int				arg_count;

	temp = *p_state;
	arg_count = 0;
	while (temp.current && temp.current->type != PIPE)
	{
		if (temp.current->type == WORD)
		{
			arg_count++;
			temp.current = temp.current->next;
		}
		else
		{
			temp.current = temp.current->next;
			if (temp.current && temp.current->type == WORD)
				temp.current = temp.current->next;
		}
	}
	return (arg_count);
}

t_redirections	*assign_redir_type(t_shell *shell, t_parser_state *p_state,
	t_redirections *redir)
{
	t_token			*token;

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
		ft_error(shell, "Invalid redirection operator");
	advance_token(p_state);
	return (redir);
}

t_hdoc	assign_hdoc_expansion(t_token *token)
{
	if (token->hdoc == EXPAND_VAR)
		return (EXPAND);
	else
		return (NO_EXPAND);
}
