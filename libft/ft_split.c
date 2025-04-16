/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:18:48 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/11/01 12:27:44 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocate (with malloc(3)) and returns an array of strings
// obtained by dividing by ’s’, using the character ’c’ as a delimiter.
// The array must end with a NULL pointer.

static size_t	ft_elem_array(const char *s, char c)
{
	size_t	i;
	size_t	array_len;
	int		word_control;

	i = 0;
	array_len = 0;
	word_control = 0;
	while (s[i])
	{
		if (s[i] != c && word_control == 0)
		{
			word_control = 1;
			array_len++;
		}
		else if (s[i] == c)
			word_control = 0;
		i++;
	}
	return (array_len);
}

static char	*ft_new_string(const char *str, unsigned int i, unsigned int start)
{
	size_t	str_len;
	char	*new_str;

	str_len = i - start;
	new_str = (char *)malloc((str_len + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_memcpy(new_str, str, str_len);
	new_str[str_len] = '\0';
	return (new_str);
}

static void	ft_free_all(char **array, unsigned int j)
{
	while (j > 0)
		free(array[--j]);
	free(array);
}

static char	*ft_allocate_array(char **array, char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			array[j] = ft_new_string(s + start, i, start);
			if (array[j] == NULL)
			{
				ft_free_all(array, j);
				return (NULL);
			}
			j++;
		}
		else
			i++;
	}
	return (*array);
}

char	**ft_split(char const *s, char c)
{
	size_t	array_len;
	char	**array;

	array_len = ft_elem_array(s, c);
	array = (char **)malloc((array_len + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	array[array_len] = NULL;
	ft_allocate_array(array, s, c);
	return (array);
}
