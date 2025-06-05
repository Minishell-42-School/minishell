/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:47:50 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/05 11:53:02 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_build(t_shell *s, t_aux *aux, char *new)
{
	int		exp_len;
	char	*var_name;

	exp_len = var_name_len(s->token_list->value + aux->i + 1);
	var_name = ft_strndup(s->token_list->value + aux->i + 1, exp_len);
	if (exp_len == 0)
	{
		new[aux->j] = '$';
		aux->j++;
		aux->i++;
	}
	else if (exp_len == 1 && var_name[0] == '?')
	{
		handle_question_mark(s, aux, new);
	}
	else
	{
		handle_env_var(s->vars, aux, new, var_name);
	}
	free(var_name);
}

static void	process_literal(t_shell *s, t_aux *aux, char *new)
{
	if (s->token_list->expand_var && s->token_list->value[aux->i] == '$'
		&& aux->k < s->token_list->nbr_env_var)
		aux->k++;
	new[aux->j] = s->token_list->value[aux->i];
	aux->j++;
	aux->i++;
}

static char	*build_expanded(t_shell *s, size_t new_len)
{
	char	*new_value;
	t_aux	aux;

	aux.i = 0;
	aux.j = 0;
	aux.k = 0;
	new_value = malloc(new_len + 1);
	if (!new_value)
		return (NULL);
	while (s->token_list->value[aux.i])
	{
		if (s->token_list->expand_var && aux.k < s->token_list->nbr_env_var
			&& s->token_list->expand_var[aux.k]
			&& s->token_list->value[aux.i] == '$')
			process_build(s, &aux, new_value);
		else
			process_literal(s, &aux, new_value);
	}
	new_value[aux.j] = '\0';
	return (new_value);
}

static int	expand_one_token(t_shell *s)
{
	size_t	new_len;
	char	*new;

	new_len = calc_new_len(s);
	new = build_expanded(s, new_len);
	if (!new)
		return (-1);
	free (s->token_list->value);
	s->token_list->value = new;
	free(s->token_list->expand_var);
	s->token_list->nbr_env_var = 0;
	s->token_list->expand_var = NULL;
	return (0);
}

void	expand_all_tokens(t_shell *s)
{
	t_token	*temp;
	t_token	*saved;

	temp = s->token_list;
	while (temp)
	{
		if (temp->nbr_env_var > 0 && ft_strcmp(temp->value, "$") != 0)
		{
			saved = s->token_list;
			s->token_list = temp;
			expand_one_token(s);
			s->token_list = saved;
		}
		temp = temp->next;
	}
}
