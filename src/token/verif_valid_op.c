/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_valid_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:42:15 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/30 17:29:46 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	verif_error(char *str, int i, char c)
{
	if (!str[i] || (is_operator(str[i]) && str[i] != c) || \
		(str[i] == c && (!str[i + 1] || is_operator(str[i + 1]))) || \
		(str[i] == '|' && c == '|'))
	{
		printf("%sError%s ~> Syntax error near redirection operator!\n", \
			RED_B, RESET);
		return (1);
	}
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
