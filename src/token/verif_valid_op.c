/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_valid_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:42:15 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/12 17:01:23 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	error_msg(char c_token, int newline_code)
{
	ft_printf_stderr(" syntax error near unexpected token ");
	if (newline_code && c_token != '|')
		ft_printf_stderr("`newline'\n");
	else
		ft_printf_stderr("`%c'\n", c_token);
	return (1);
}

static int	verif_error(char *str, int i, char c)
{
	if (!str[i] || (str[i] == c && !str[i + 1]))
		return (error_msg(c, 1));
	else if ((is_operator(str[i]) && \
			str[i] != c) || (str[i] == '|' && c == '|'))
		return (error_msg(str[i], 0));
	else if (str[i] == c && is_operator(str[i + 1]))
		return (error_msg(str[i + 1], 0));
	return (0);
}

int	verif_valid_op(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = '\0';
		if (is_operator(str[i]) && !quote)
		{
			i++;
			if (verif_error(str, i, str[i - 1]))
				return (1);
			else if (!is_operator(str[i]))
				i--;
		}
		i++;
	}
	return (0);
}
