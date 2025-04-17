/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:42:15 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/16 18:06:02 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_type	verif_type(char *str)
{
	t_token_type	type;

	if (str[0] == '<' && !str[1])
		type = REDIR_IN;
	else if (str[0] == '>' && !str[1])
		type = REDIR_OUT;
	else if (str[0] == '<' && str[1] == '<')
		type = REDIR_DELIMITER;
	else if (str[0] == '>' && str[1] == '>')
		type = REDIR_APPEND;
	else if (str[0] == '|')
		type = PIPE;
	else
		type = WORD;
	return (type);
}

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

// char	*clean_dobleq(char *str)
// {
// 	int	i;
// 	int	j;
//   int len;
// 	char	*new_str;

//   len = ft_strlen(str);
//   if (str[0] == 34 && str[len] == 34)
//   {
//     new_str = malloc(len - 2);
//     if (!new_str)
//       return (NULL);
//   }
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == 34)
// 			i++;
//     else
//     {
//       new_str[j] = str[i];
//       i++;
//       j++;
//     }
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);
// }

// char	*verif_quote(char **str, int *i)
// {
// 	char	*new_str;
// 	int		ind;

// 	ind = *i;
// 	if (ft_strchr(str[ind], 34)) // doble quote
// 	{
//     new_str = str[ind];
//     if (ft_strchr(str[ind], 34) == ft_strrchr(str[ind], 34))
//     {
//       ind++;
//       new_str = ft_strjoin(new_str, " ");
//       while (!ft_strchr(str[ind], 34))
//       {
//         new_str = ft_strjoin(new_str, str[ind]);
//         new_str = ft_strjoin(new_str, " ");
//         ind++;
//       }
//     }
//     new_str = clean_dobleq(new_str);
//     // new_str = ft_strtrim(new_str, (const char)34);
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


char	*verif_quote(char **str, int *i)
{
	char	*new_str;
	int		ind;

	ind = *i;
	if (ft_strchr(str[ind], 34)) // doble quote
	{
		new_str = str[ind];
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
	else if (ft_strchr(str[ind], 39)) // single quote
	{
		new_str = clean_quote(str[ind]);
	}
	else
		new_str = str[ind];
	*i = ind;
	return (new_str);
}

void	get_token(t_token **token_list, char *input)
{
	int				i;
	char			*t_value;
	char			**input_array;
	t_token_type	t_type;

	i = 0;
	// if (input == "")
	// 	return ;
	input_array = ft_split(input, ' ');
	while (input_array[i])
	{
		t_value = verif_quote(input_array, &i);
		t_type = verif_type(t_value);
		create_token(token_list, t_value, t_type);
		i++;
	}
}
