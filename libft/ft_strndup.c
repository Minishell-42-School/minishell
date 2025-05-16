/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:03:43 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/16 14:50:14 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h" // Include your libft header

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new_str;

	if (!s)
		return (NULL);
	len = 0;
	while (len < n && s[len])
		len++;
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s, len);
	new_str[len] = '\0';
	return (new_str);
}
