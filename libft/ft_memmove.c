/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:23:09 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/21 16:30:37 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copies n bytes from memory area src to memory area dest.
// The memory areas may overlap: copying takes place as though the bytes
// in src are first copied into a temporary array that does not overlap
// src or dest, and the bytes are then copied from the temporary array to dest.

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	size_t				i;

	s = (const unsigned char *)src;
	i = 0;
	if ((unsigned char *)dest == NULL && s == NULL)
		return (NULL);
	if ((unsigned char *)dest > s && (unsigned char *)dest < s + n)
	{
		while (n > 0)
		{
			((unsigned char *)dest)[n - 1] = s[n - 1];
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = s[i];
			i++;
		}
	}
	return (dest);
}
