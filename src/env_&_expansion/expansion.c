/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:47:50 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/11 17:47:29 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_get(t_var *vars, const char *key)
{
	t_var *v;

	v = var_find(vars, key);
	if(v)
		return (v->value);
	else
		return (NULL);
}

void	expand_all_tokens(t_token *head, t_var *vars)
{
	while (head)
	{
		if (head->nbr_env_var > 0)
			expand_one_token(head, vars);
		head = head->next;
	}
}
//what happens if there is out of bounds access in "tok->expand_var[k]"?
int	expand_one_token(t_token *tok, t_var *vars)
{
	char	*old_value;
	int		i;
	int		k;

	k = 0;
	i = 0;
	old_value = tok->value;
	
	while (old_value[i])
	{
		if(tok->expand_var && tok->expand_var[k] && old_value[i] == '$')
		{
			
		}
		i++;
	}
}