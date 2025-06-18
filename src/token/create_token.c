/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:59 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/18 17:48:55 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_token(void)
{
	t_token	*new_t;

	new_t = malloc(sizeof(t_token));
	if (!new_t)
	{
		printf_stderr("Malloc error at new_token");
		return (NULL);
	}
	new_t->type = WORD;
	new_t->value = NULL;
	new_t->hdoc = R_NO_HDOC;
	new_t->ign_value = 0;
	new_t->nbr_env_var = 0;
	new_t->expand_var = NULL;
	new_t->next = NULL;
	return (new_t);
}

void	add_back(t_token **token, t_token *new_t)
{
	t_token	*temp;

	if (!token || !new_t)
		return ;
	if (!*token)
	{
		*token = new_t;
		return ;
	}
	temp = *token;
	while (temp->next)
		temp = temp->next;
	temp->next = new_t;
}
