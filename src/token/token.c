/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:42:15 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/05 18:33:53 by jcosta-b         ###   ########.fr       */
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

static void	hdoc_exp(t_token *token, char input, int control)
{
  if (control == 1)
  {
    if (input == '\'' || input == '\"')
      token->hdoc = NO_EXPAND_VAR;
    else
      token->hdoc = EXPAND_VAR;
  }
}

static void	handle_control(t_token *token, int *control)
{
  if (token->type == REDIR_HEREDOC)
    (*control) = 1;
  else
    (*control) = 0;
}

void	get_token(t_token **token_list, char *input)
{
	int		i;
	int		hdoc_control;
	t_token	*new_token;

	i = 0;
	if (!verif_close_q(input) || verif_valid_op(input) || *input == '\0')
    return ;
	hdoc_control = 0;
	while (input[i])
	{
		new_token = init_token();
		if (!new_token)
			return ;
		while (is_wspace(input[i]))
			i++;
    hdoc_exp(new_token, input[i], hdoc_control);
		if (is_operator(input[i]))
			new_token->value = read_operator(input, &i, new_token);
		else
			new_token->value = read_token(input, &i, new_token);
    handle_control(new_token, &hdoc_control);
		add_back(token_list, new_token);
	}
	verif_value(token_list);
}
