/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:06:10 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/30 17:19:20 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function locates the first occurrence of the
// null-terminated string little in the string big, where not
// more than len characters are searched

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (i <= len - little_len && big[i])
	{
		j = 0;
		while (j < little_len && big[i + j] == little[j])
			j++;
		if (j == little_len && little_len <= len)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
