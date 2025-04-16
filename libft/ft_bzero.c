/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:29 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/30 15:03:41 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function erases the data in the n bytes of the memory starting at
// the location pointed to by s, by writing zeros.

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}
