/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:23:56 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/03 15:27:37 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_get(t_var *vars, const char *key)
{
	t_var	*v;

	v = var_find(vars, key);
	if (v)
		return (v->value);
	else
		return (NULL);
}

static size_t	digit_count(int n)
{
	size_t	digits;
	long	val;

	val = n;
	digits = 0;
	if (val <= 0)
	{
		digits = 1;
		val = -val;
	}
	while (val > 0)
	{
		val /= 10;
		digits++;
	}
	return (digits);
}

size_t	calc_new_len(t_shell *s)
{
	t_aux	aux;
	size_t	len;

	aux.i = 0;
	aux.k = 0;
	len = 0;
	while (s->token_list->value[aux.i])
	{
		if (s->token_list->value[aux.i] == '$'
			&& s->token_list->value[aux.i + 1]
			&& s->token_list->value[aux.i + 1] == '?')
		{
			len += digit_count(s->last_status);
			aux.i += 2;
			continue ;
		}
		if (s->token_list->expand_var
			&& aux.k < s->token_list->nbr_env_var
			&& s->token_list->expand_var[aux.k]
			&& s->token_list->value[aux.i] == '$')
		{
			process_env_flags(s->token_list, &aux, &len, s->vars);
		}
		else
		{
			len++;
			if (s->token_list->expand_var
				&& s->token_list->value[aux.i] == '$'
				&& aux.k < s->token_list->nbr_env_var)
				aux.k++;
			aux.i++;
		}
	}
	return (len);
}


void	process_env_flags(t_token *tok, t_aux *aux,
	size_t *len, t_var *vars)
{
	char	*new_value;
	int		exp_len;
	char	*var_name;

	exp_len = var_name_len(tok->value + aux->i + 1);
	var_name = ft_strndup(tok->value + aux->i + 1, exp_len);
	new_value = var_get(vars, var_name);
	free(var_name);
	if (new_value)
		*len += ft_strlen(new_value);
	aux->i += exp_len + 1;
	aux->k++;
}

int	var_name_len(char *tok_val)
{
	int	len;

	len = 0;
	while ((tok_val[len] >= 'A' && tok_val[len] <= 'Z')
		|| (tok_val[len] >= 'a' && tok_val[len] <= 'z')
		|| (tok_val[len] >= '0' && tok_val[len] <= '9')
		|| tok_val[len] == '_')
		len++;
	return (len);
}
