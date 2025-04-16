/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:00:32 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/30 11:10:10 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Deletes and frees the specified node and all successors
// of this node, using the ’del’ and free(3) functions.
// At the end, the pointer to the list must be set to NULL.

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_node;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		next_node = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next_node;
	}
	*lst = NULL;
}
