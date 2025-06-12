/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:42:15 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/12 17:13:31 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_wspace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	hdoc_exp(t_token *token, char input, int control)
{
	if (control == 1)
	{
		if (input == '\'' || input == '\"')
			token->hdoc = NO_EXPAND_VAR;
		else
			token->hdoc = EXPAND_VAR;
	}
}

void	handle_control(t_token *token, int *control)
{
	if (token->type == REDIR_HEREDOC)
		(*control) = 1;
	else
		(*control) = 0;
}
