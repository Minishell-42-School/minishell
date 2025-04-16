/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:54:17 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/31 11:44:59 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocate (with malloc) and return a copy of 's1' with the 
// specified characteres removed of begin and of the end from 'set'.

static size_t	ft_start(char const *s1, char const *set)
{
	size_t	begin;
	size_t	i;

	i = 0;
	begin = 0;
	while (s1[i] && ft_strchr(set, s1[i]) != NULL)
	{
		begin++;
		i++;
	}
	return (begin);
}

static size_t	ft_end(char const *s1, char const *set)
{
	size_t	end;
	size_t	i;

	i = ft_strlen(s1);
	end = 0;
	while (i > 0 && ft_strchr(set, s1[i]) != NULL)
	{
		end++;
		i--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	size_t	new_len;
	size_t	begin;
	size_t	end;
	size_t	i;

	begin = ft_start(s1, set);
	end = 0;
	i = 0;
	if (begin < ft_strlen(s1))
		end = ft_end(s1, set);
	if (ft_strlen(s1) == begin)
		new_len = 0;
	else
		new_len = ft_strlen(s1) - begin - end + 1;
	newstr = (char *)malloc((new_len + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	newstr[new_len] = '\0';
	while ((i + begin) <= (ft_strlen(s1) - end))
	{
		newstr[i] = s1[i + begin];
		i++;
	}
	return (newstr);
}
