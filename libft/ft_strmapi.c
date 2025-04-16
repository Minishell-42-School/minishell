/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:24:06 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/25 14:52:43 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Apply the function ’f’ to each character of the string ’s’,
// passes its index as the first argument to create a new string
// (with malloc(3)) resulting from successive applications of ’f’.

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len;
	char			*newstr;

	len = ft_strlen(s);
	newstr = (char *)malloc((len + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
