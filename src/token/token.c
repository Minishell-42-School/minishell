/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:42:15 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/17 18:05:20 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	is_wspace(char c)
{
  return (c == ' ' || c == '\t');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token_type	get_type(char *str, int i)
{
	t_token_type	type;

  if (str[i] == '|' && !is_operator(str[i + 1]))
    type = PIPE;
  else if (str[i] == '<')
  {
    if (!is_operator(str[i + 1]))
      type = REDIR_IN;
    else if (str[i + 1] == '<' && !is_operator(str[i + 2]))
      type = REDIR_DELIMITER;
  }
  else if (str[i] == '>')
  {
    if (!is_operator(str[i + 1]))
      type = REDIR_OUT;
    else if (str[i + 1] == '>' && !is_operator(str[i + 2]))
      type = REDIR_APPEND;
  }
  else
    type = WORD;
	return (type);
}

char  *read_operator(char *str, int *i, t_token_type *type)
{
  int   start;

  start = *i;
  *type = get_type(str, *i);
  if ((str[*i] == '|' && !is_operator(str[*i + 1])) ||
      (!is_operator(str[*i + 1]) || !str[*i + 1]))
  {
    (*i)++;
    return (ft_substr(str, start, 1));
  }
  else
  {
    if (str[*i + 1] == str[*i] && !is_operator(str[*i + 2]))
    {
      *i += 2;
      return (ft_substr(str, start, 2));;
    }
    else
    {
      while (is_operator(str[*i]))
        (*i)++; // MSG DE ERROR -> BREAK
      *type = WORD;
      return (ft_substr(str, start, (*i - start)));
    }
  }
}

void	get_token(t_token **token_list, char *input)
{

	int i;
  t_token_type type;
  char  *value;
  int *expand;
  int nbr_env;

  i = 0;
  if (!verif_close_q(input))
  {
    printf("%sError%s ~> Quote still open!\n", RED_B, RESET);
    return ;
  }
	while (input[i])
	{
    nbr_env = 0;
    expand = NULL;
		while (is_wspace(input[i]))
      i++;
    if (is_operator(input[i]))
      value = read_operator(input, &i, &type);
    else
    {
      type = WORD;
      value = read_token(input, &i, &nbr_env, &expand);
    }
    create_token(token_list, value, type, nbr_env, expand);
  }
}
