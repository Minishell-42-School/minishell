/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:12:18 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/23 11:45:58 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function concatenate strings. both src and dst must be NUL-terminated.

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;
	size_t	to_copy;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	to_copy = size - dest_len - 1;
	i = 0;
	if (size == 0 || dest_len >= size)
		return (size + src_len);
	if (to_copy > src_len)
		to_copy = src_len;
	while (i < to_copy)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + to_copy] = '\0';
	return (dest_len + src_len);
}
