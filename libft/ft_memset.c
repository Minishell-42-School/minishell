/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:26:38 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/11/01 12:25:11 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function fills the first n bytes of the memory area
// pointed to by s with the constant byte c.

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	value;

	value = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = value;
		i++;
	}
	return (s);
}
