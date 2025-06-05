/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:42:15 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/05 16:27:47 by jcosta-b         ###   ########.fr       */
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

// void	get_token(t_token **token_list, char *input)
// {
// 	int		i;
// 	t_token	*new_token;

// 	i = 0;
// 	if (!verif_close_q(input) || verif_valid_op(input) || *input == '\0')
// 		return ;
// 	while (input[i])
// 	{
// 		new_token = init_token();
// 		if (!new_token)
// 			return ;
// 		while (is_wspace(input[i]))
// 			i++;
// 		if (is_operator(input[i]))
// 			new_token->value = read_operator(input, &i, new_token);
// 		else
// 			new_token->value = read_token(input, &i, new_token);
// 		add_back(token_list, new_token);
// 	}
// 	verif_value(token_list);
// }

void	get_token(t_token **token_list, char *input)
{
	int		i;
	int		hdoc_control;
	t_token	*new_token;

	i = 0;
	hdoc_control = 0;
	if (!verif_close_q(input) || verif_valid_op(input) || *input == '\0')
		return ;
	while (input[i])
	{
		new_token = init_token();
		if (!new_token)
			return ;
		while (is_wspace(input[i]))
			i++;
		if (is_operator(input[i]))
			new_token->value = read_operator(input, &i, new_token, &hdoc_control);
		else
			new_token->value = read_token(input, &i, new_token, &hdoc_control);
		add_back(token_list, new_token);
	}
	verif_value(token_list);
}
