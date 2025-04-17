/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:42:15 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/17 18:05:20 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_type	verif_type(char *str)
{
	t_token_type	type;

	if (str[0] == '<' && !str[1])
		type = REDIR_IN;
	else if (str[0] == '>' && !str[1])
		type = REDIR_OUT;
	else if (str[0] == '<' && str[1] == '<' && !str[2])
		type = REDIR_DELIMITER;
	else if (str[0] == '>' && str[1] == '>' && !str[2])
		type = REDIR_APPEND;
	else if (str[0] == '|' && !str[1])
		type = PIPE;
	else if (str[0] == '$')
		type = ENV_VAR;
	else
		type = WORD;
	return (type);
}

void	get_token(t_token **token_list, char *input)
{
	int				i;
	int				error_code;
	char			*t_value;
	char			**input_array;
	t_token_type	t_type;

	i = 0;
	// if (input == "")
	// 	return ;
	error_code = 0;
	input_array = ft_split(input, ' ');
	while (input_array[i])
	{
		t_value = verif_quote(input_array, &i, &error_code);
		if (error_code)
		{
			printf("%sError%s -> Double quote still open\n", RED_B, RESET);
			return ;
		}
		t_type = verif_type(t_value);
		create_token(token_list, t_value, t_type);
		i++;
	}
	free(input_array);
}
