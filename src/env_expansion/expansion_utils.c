/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:23:56 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/16 14:50:59 by ekeller-@st      ###   ########.fr       */
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

size_t	calc_new_len(t_token *tok, t_var *vars)
{
	t_exp_aux	aux;
	size_t		len;

	aux.i = 0;
	aux.k = 0;
	len = 0;
	while (tok->value[aux.i])
	{
		if (tok->expand_var && aux.k < tok->nbr_env_var
			&& tok->expand_var[aux.k] && tok->value[aux.i] == '$')
			process_env_flags(tok, &aux, &len, vars);
		else
		{
			len++;
			if (tok->expand_var && tok->value[aux.i] == '$'
				&& aux.k < tok->nbr_env_var)
				aux.k++;
			aux.i++;
		}
	}
	return (len);
}

void	process_env_flags(t_token *tok, t_exp_aux *aux,
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
