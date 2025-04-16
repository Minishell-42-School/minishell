/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:39:20 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/11/01 16:53:04 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function scans the initial n bytes of the memory
// area pointed to by s for the first instance of c.

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	unsigned char	*ptr;
	unsigned char	ch;

	ptr = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == ch)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}
