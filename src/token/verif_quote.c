/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:02:00 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/28 12:00:40 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	nbr_quotes(char *str, int *i, char c)
{
	int	nbr;

	nbr = 0;
	nbr++;
	(*i)++;
	if (!str[*i])
		return (nbr);
	while (str[*i] != c && str[*i])
		(*i)++;
	if (str[*i] == c)
	{
		nbr++;
		(*i)++;
	}
	return (nbr);
}

int	verif_close_q(char *str)
{
	int	single_q;
	int	double_q;
	int	i;

	single_q = 0;
	double_q = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			double_q += nbr_quotes(str, &i, str[i]);
		else if (str[i] == '\'')
			single_q += nbr_quotes(str, &i, str[i]);
		else
			i++;
	}
	if (single_q % 2 == 0 && double_q % 2 == 0)
		return (1);
	else
		printf("%sError%s ~> Quote still open!\n", RED_B, RESET);
	return (0);
}
