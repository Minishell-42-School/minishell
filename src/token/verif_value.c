/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:42:15 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/23 11:48:59 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	del_last_token(t_token **token_list)
{
	t_token	*temp;
	t_token	*del_token;

	if (!(*token_list)->next)
		return ;
	else
	{
		temp = *token_list;
		while (temp->next->next)
			temp = temp->next;
		del_token = temp->next;
		temp->next = NULL;
		if (del_token->expand_var)
			free(del_token->expand_var);
		free(del_token);
	}
	verif_value(token_list);
}

void	verif_value(t_token **token_list)
{
	t_token	*temp;

	if (!token_list)
		return ;
	temp = *token_list;
	while (temp->next)
		temp = temp->next;
	if (!temp->value)
		del_last_token(token_list);
}
