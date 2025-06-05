/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:02:00 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/05 16:22:11 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	nbr_var(char *str, t_token *token)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			token->nbr_env_var++;
		i++;
	}
}

static void	init_expand(t_token *token)
{
	int	i;

	i = 0;
	if (token->nbr_env_var > 0)
	{
		token->expand_var = malloc(token->nbr_env_var * sizeof(int));
		if (!token->expand_var)
			return ;
		while (i < token->nbr_env_var)
		{
			token->expand_var[i] = 1;
			i++;
		}
	}
}

static void	get_expand(char *str, t_token *token)
{
	int		i;
	int		i_exp;
	char	quote;

	i = 0;
	i_exp = 0;
	quote = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote)
			quote = str[i];
		else if (quote == str[i] && quote)
			quote = '\0';
		if (str[i] == '$')
		{
			if (quote == '\'')
				token->expand_var[i_exp] = 0;
			i_exp++;
		}
		i++;
	}
}

void	verif_env_var(char *str, t_token *token)
{
	printf("%s\n", str);
	nbr_var(str, token);
	if (token->nbr_env_var > 0)
	{
		init_expand(token);
		if (!token->expand_var)
			return ;
		get_expand(str, token);
	}
}
