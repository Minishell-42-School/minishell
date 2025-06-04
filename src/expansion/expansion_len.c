/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:04:55 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/04 15:16:11 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	*i += 2;
	return (digits);
}

static int	check_if_interrogation(t_token *t, t_aux *aux, t_shell *s)
{
	if (t->value[aux->i] == '$' && t->value[aux->i + 1]
		&& t->value[aux->i + 1] == '?')
	{
		aux->len += digit_count(s->last_status, &aux->i);
		return (0);
	}
	return (1);
}

static size_t	free_aux_return_len(t_aux *aux)
{
	size_t	len;

	len = aux->len;
	if (aux)
		free(aux);
	return (len);
}

static void	process_env_flags(t_token *tok, t_aux *aux, t_var *vars)
{
	char	*new_value;
	int		exp_len;
	char	*var_name;

	exp_len = var_name_len(tok->value + aux->i + 1);
	if (exp_len == 0)
	{
		aux->len++;
		aux->i++;
		aux->k++;
		return ;
    }
	var_name = ft_strndup(tok->value + aux->i + 1, exp_len);
	new_value = var_get(vars, var_name);
	free(var_name);
	if (new_value)
		aux->len += ft_strlen(new_value);
	aux->i += exp_len + 1;
	aux->k++;
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
