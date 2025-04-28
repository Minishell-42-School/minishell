/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:51:51 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/28 14:53:47 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_all(t_token **token_lst)
{
	t_token	*tmp;

	if (!token_lst || !*token_lst)
		return ;
	while (*token_lst)
	{
		tmp = (*token_lst)->next;
		if ((*token_lst)->value)
			free((*token_lst)->value);
		if ((*token_lst)->expand_var)
			free((*token_lst)->expand_var);
		free(*token_lst);
		*token_lst = tmp;
	}
}
