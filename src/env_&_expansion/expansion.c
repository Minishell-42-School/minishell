/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:47:50 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/12 18:26:27 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_all_tokens(t_token *head, t_var *vars)
{
	while (head)
	{
		if (head->nbr_env_var > 0)
			expand_one_token(head, vars);
		head = head->next;
	}
}

int	expand_one_token(t_token *tok, t_var *vars)
{
	size_t	new_len;
	char	*new;
	
	new_len = calc_new_len(tok, vars);
	new = build_expanded(tok->value, tok->expand_var, vars, new_len);
	if (!new)
		return (-1);
	free (tok->value);
	free (tok->expand_var);
	tok->value = new;
	tok->nbr_env_var = 0;
	tok->expand_var = NULL;
	return (0);
}

char	*build_expanded()