/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:59 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/16 17:59:18 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*init_token(char *t_value, t_token_type t_type, int nbr_env, int *expand)
{
	t_token	*new_t;

	new_t = malloc(sizeof(t_token));
	if (!new_t)
		return (NULL);
	new_t->type = t_type;
	new_t->value = t_value;
  new_t->nbr_env_var = nbr_env;
  new_t->expand_var = expand;
	new_t->next = NULL;
	return (new_t);
}

static void	add_back(t_token **token, t_token *new)
{
	t_token	*temp;

	if (!token || !new)
		return ;
	if (!*token)
	{
		*token = new;
		return ;
	}
	temp = *token;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	create_token(t_token **token, char *t_value, t_token_type t_type, int nbr_env, int *expand)
{
	t_token *new_token;

	new_token = init_token(t_value, t_type, nbr_env, expand);
	if(!new_token)
		return ;
	add_back(token, new_token);
}
