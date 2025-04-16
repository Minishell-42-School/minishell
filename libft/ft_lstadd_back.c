/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:56:36 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/30 12:39:59 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Adds the ’new’ node to the end of the list.

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_p;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_p = ft_lstlast(*lst);
	last_p->next = new;
}
