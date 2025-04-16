/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:24:29 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/30 15:24:32 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// it allocates memory for an array of nmemb elements of size bytes each 
// and returns a pointer to the allocated memory. The memory is set to zero.

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb != 0 && size > (size_t) - 1 / nmemb)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
