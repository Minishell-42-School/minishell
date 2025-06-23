/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:42:15 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/23 12:12:54 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	token_loop(t_token **token_list, char *input)
{
	int		i;
	int		hdoc_control;
	t_token	*new_token;

	i = 0;
	hdoc_control = 0;
	while (input[i])
	{
		new_token = init_token();
		if (!new_token)
			return (1);
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
	return (0);
}

int	get_token(t_token **token_list, char *input)
{
	if (*input == '\0')
		return (0);
	if (!verif_close_q(input) || verif_valid_op(input))
		return (1);
	if (token_loop(token_list, input))
		return (1);
	if (!(*token_list)->next && (*token_list)->ign_value)
	{
		free_token_lst(token_list);
		return (0);
	}
	verif_value(token_list);
	return (0);
}
