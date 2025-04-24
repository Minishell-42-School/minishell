/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:02:00 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/17 17:59:39 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int nbr_q(char *str)
{
  int   i;
  int   count;
	char	quote;

  i = 0;
  count = 0;
  quote = '\0';
  while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote)
    {
			quote = str[i];
      count++;
    }
		else if (str[i] == quote)
    {
      quote = '\0';
      count++;
    }
		i++;
	}
  return (count);
}

static char	*clean_quote(char *str)
{
	int		i;
  int   j;
	char	quote;
	char	*clean_str;

  clean_str = malloc((ft_strlen(str) - nbr_q(str) + 1) * sizeof(char));
	if (!clean_str)
		return (NULL);
  i = 0;
  j = 0;
  quote = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = '\0';
		else
			clean_str[j++] = str[i];
		i++;
	}
	clean_str[j] = '\0';
	return (clean_str);
}

void  verif_env_var(char *str, int *nbr_env, int **expand)
{
  int i;
  char	quote;
  int   i_exp;

  i = 0;
  while (str[i])
  {
    if (str[i] == '$')
    (*nbr_env)++;
    i++;
  }
  i = 0;
  quote = '\0';
  if (*nbr_env > 0)
  {
    *expand = malloc(*nbr_env * sizeof(int));
    if (!(*expand))
      return ;
    i_exp = 0;
    while (i_exp < *nbr_env)
    {
      (*expand)[i_exp] = 1;
      i_exp++;
    }
    i_exp = 0;
    while (str[i])
    {
      if ((str[i] == '\'' || str[i] == '\"') && !quote)
        quote = str[i];
      else if (quote == str[i] && quote)
        quote = '\0';
      if (str[i] == '$')
      {
        if (quote == '\'')
          (*expand)[i_exp] = 0;
        i_exp++;
      }
      i++;
    }
  }
}

char	*read_token(char *str, int *i, int *nbr_env, int **expand)
{
	int		start;
	char	quote;
  char *temp;
  char *clean_token;

  start = *i;
	quote = 0;
	while (str[*i])
	{
		if ((str[*i] == '\'' || str[*i] == '\"') && !quote)
      quote = str[*i];
		else if (quote == str[*i] && quote)
      quote = '\0';
		else if (!quote && (is_wspace(str[*i]) || is_operator(str[*i])))
			break;
		(*i)++;
	}
	temp = ft_substr(str, start, (*i - start));
  verif_env_var(temp, nbr_env, expand);
	clean_token = clean_quote(temp);
	free(temp);
	return (clean_token);
}
