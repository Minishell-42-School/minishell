/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:04:11 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/30 11:11:11 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns the last node of a list.

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*p;

	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			p = lst;
		lst = lst->next;
	}
	return (p);
}
