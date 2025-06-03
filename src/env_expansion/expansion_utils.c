/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:23:56 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/03 17:32:07 by ekeller-@st      ###   ########.fr       */
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

static size_t	digit_count(int n, int *i)
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
	i += 2;
	return (digits);
}

statict int	check_if_interrogation(t_token *t, t_aux *aux, t_shell *s)
{
	if (t->value[aux->i] == '$' && t->value[aux->i + 1]
			&& t->value[aux->i + 1] == '?')
	{
		aux->len += digit_count(s->last_status, &aux->i);
		return (0);
	}
	return (1);	
}

static size_t free_aux_return_len(t_aux *aux)
{
	size_t	len;

	len = aux->len;
	if (aux)
		free(aux);
	return (len);
}

size_t	calc_new_len(t_shell *s)
{
	t_aux	*aux;
	t_token	*t;

	aux = malloc(sizeof(t_aux));
	aux->i = 0;
	aux->k = 0;
	aux->len = 0;
	t = s->token_list;
	while (t->value[aux->i])
	{
		if (check_if_interrogation(t, aux, s) == 0)
			continue ;
		if (t->expand_var && aux->k < t->nbr_env_var
			&& t->expand_var[aux->k] && t->value[aux->i] == '$')
			process_env_flags(t, aux, s->vars);
		else
		{
			aux->len++;
			if (t->expand_var && t->value[aux->i] == '$'
				&& aux->k < t->nbr_env_var)
				aux->k++;
			aux->i++;
		}
	}
	return (free_aux_return_len(aux));
}

void	process_env_flags(t_token *tok, t_aux *aux, t_var *vars)
{
	char	*new_value;
	int		exp_len;
	char	*var_name;

	exp_len = var_name_len(tok->value + aux->i + 1);
	var_name = ft_strndup(tok->value + aux->i + 1, exp_len);
	new_value = var_get(vars, var_name);
	free(var_name);
	if (new_value)
		aux->len += ft_strlen(new_value);
	aux->i += exp_len + 1;
	aux->k++;
}

int	var_name_len(char *tok_val)
{
	int	len;

	len = 0;
	if (tok_val[0] == '?')
		return (1);
	while ((tok_val[len] >= 'A' && tok_val[len] <= 'Z')
		|| (tok_val[len] >= 'a' && tok_val[len] <= 'z')
		|| (tok_val[len] >= '0' && tok_val[len] <= '9')
		|| tok_val[len] == '_')
		len++;
	return (len);
}
