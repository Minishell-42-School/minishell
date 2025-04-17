/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:02:00 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/17 13:47:18 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 39)
			count++;
		i++;
	}
	return (count);
}

char	*clean_quote(char *str)
{
	int	i;
	int	j;
	char	*new_str;

	new_str = malloc(ft_strlen(str) - count_quote(str));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == 39)
			i++;
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*clean_dobleq(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = malloc(len - 2);
	if (!new_str)
		return (NULL);
	// if (str[0] == 34 && str[len] == 34)
	// {
	// }
	i = 1;
	j = 0;
	while (i < (len - 1))
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	verif_closeq(char **str, int i)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	
	if (ft_strchr(str[i], 34) != ft_strrchr(str[i], 34))
		return (1);
	else if (i < (len - 1))
	{
		i++;
		while (!ft_strchr(str[i], 34) && i < (len - 1))
			i++;
		if (ft_strchr(str[i], 34))
			return (1);
	}
	return (0);
}


char	*verif_quote(char **str, int *i)
{
	char	*new_str;
	int		ind;

	ind = *i;
	if (ft_strchr(str[ind], 34)) // doble quote
	{
		if (!verif_closeq(str, ind))
			return (new_str = "ERROR"); // FAZER Tratamento de erro!!!!
		new_str = str[ind];
		if (ft_strchr(str[ind], 34) == ft_strrchr(str[ind], 34))
		{
			ind++;
			new_str = ft_strjoin(new_str, " ");
			while (!ft_strchr(str[ind], 34))
			{
				new_str = ft_strjoin(new_str, str[ind]);
				new_str = ft_strjoin(new_str, " ");
				ind++;
			}
			new_str = ft_strjoin(new_str, str[ind]);
		}
		new_str = clean_dobleq(new_str);
		// new_str = ft_strtrim(new_str, (const char)34);
	}
	else if (ft_strchr(str[ind], 39)) // single quote
	{
		new_str = clean_quote(str[ind]);
	}
	else
		new_str = str[ind];
	*i = ind;
	return (new_str);
}


// char	*verif_quote(char **str, int *i)
// {
// 	char	*new_str;
// 	int		ind;

// 	ind = *i;
// 	if (ft_strchr(str[ind], 34)) // doble quote
// 	{
// 		new_str = str[ind];
// 		ind++;
// 		new_str = ft_strjoin(new_str, " ");
// 		while (!ft_strchr(str[ind], 34))
// 		{
// 			new_str = ft_strjoin(new_str, str[ind]);
// 			new_str = ft_strjoin(new_str, " ");
// 			ind++;
// 		}
// 		new_str = ft_strjoin(new_str, str[ind]);
// 	}
// 	else if (ft_strchr(str[ind], 39)) // single quote
// 	{
// 		new_str = clean_quote(str[ind]);
// 	}
// 	else
// 		new_str = str[ind];
// 	*i = ind;
// 	return (new_str);
// }