/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:47:50 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/02 17:58:44 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*build_expanded(t_token *tok, t_var *vars, size_t new_len);
static void	process_build(t_token *tok, t_aux *aux, t_var *vars, char *new);
static void	process_literal(t_token *tok, t_aux *aux, char *new);

void	expand_all_tokens(t_token *head, t_var *vars)
{
	while (head)
	{
		if (head->nbr_env_var > 0)
			expand_one_token(head, vars);
		head = head->next;
	}
}

int	expand_one_token(t_token *tok, t_var *vars)
{
	size_t	new_len;
	char	*new;

	new_len = calc_new_len(tok, vars);
	new = build_expanded(tok, vars, new_len);
	if (!new)
		return (-1);
	free (tok->value);
	tok->value = new;
	free(tok->expand_var);
	tok->nbr_env_var = 0;
	tok->expand_var = NULL;
	return (0);
}

static char	*build_expanded(t_token *tok, t_var *vars, size_t new_len)
{
	char	*new_value;
	t_aux	aux;

	aux.i = 0;
	aux.j = 0;
	aux.k = 0;
	new_value = malloc(new_len + 1);
	if (!new_value)
		return (NULL);
	while (tok->value[aux.i])
	{
		if (tok->expand_var && aux.k < tok->nbr_env_var
			&& tok->expand_var[aux.k]
			&& tok->value[aux.i] == '$')
			process_build(tok, &aux, vars, new_value);
		else
			process_literal(tok, &aux, new_value);
	}
	new_value[aux.j] = '\0';
	return (new_value);
}

static void	process_build(t_token *tok, t_aux *aux, t_var *vars, char *new)
{
	char	*exp_value;
	int		exp_len;
	char	*var_name;

	exp_len = var_name_len(tok->value + aux->i + 1);
	var_name = ft_strndup(tok->value + aux->i + 1, exp_len);
	exp_value = var_get(vars, var_name);

	// char	*last_exit;
	// last_exit = ft_itoa(shell->last_status);
	// if (!exp_value && ft_strcmp(&tok->value[1], "?") == 0)
	// 	exp_value = last_exit;

	if (exp_value)
	{
		ft_memcpy(new + aux->j, exp_value, ft_strlen(exp_value));
		aux->j += ft_strlen(exp_value);
	}
	free(var_name);
	aux->i += exp_len + 1;
	aux->k++;
}

static void	process_literal(t_token *tok, t_aux *aux, char *new)
{
	if (tok->expand_var && tok->value[aux->i] == '$'
		&& aux->k < tok->nbr_env_var)
		aux->k++;
	new[aux->j] = tok->value[aux->i];
	aux->j++;
	aux->i++;
}
