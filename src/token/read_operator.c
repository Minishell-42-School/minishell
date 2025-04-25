/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:42:15 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/17 18:05:20 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token_type	get_type(char *str, int i)
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

char  *read_operator(char *str, int *i, t_token *token)
{
  int   start;

  start = *i;
  token->type = get_type(str, *i);
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
      token->type = WORD;
      return (ft_substr(str, start, (*i - start)));
    }
  }
}
