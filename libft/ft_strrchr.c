/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:40:55 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/30 17:15:09 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function returns a pointer to the last occurrence
// of the character c in the string s.

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	int				last_c;
	unsigned char	ch;

	i = 0;
	last_c = -1;
	ch = (unsigned char)c;
	if (ch == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == ch)
			last_c = i;
		i++;
	}
	if (last_c >= 0)
		return ((char *)&s[last_c]);
	return (NULL);
}
