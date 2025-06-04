/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:23:56 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/04 11:18:20 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	handle_env_var(t_var *vars, t_aux *aux, char *new, char *var_name)
{
	char	*exp_value;
	int		exp_len;
	int		len;

	exp_len = ft_strlen(var_name);
	exp_value = var_get(vars, var_name);
	if (exp_value)
	{
		len = ft_strlen(exp_value);
		ft_memcpy(new + aux->j, exp_value, len);
		aux->j += len;
	}
	aux->i += exp_len + 1;
	aux->k++;
}

int	handle_question_mark(t_shell *s, t_aux *aux, char *new)
{
	char	*last_exit;
	int		len;

	last_exit = ft_itoa(s->last_status);
	if (last_exit)
	{
		len = ft_strlen(last_exit);
		ft_memcpy(new + aux->j, last_exit, len);
		aux->j += len;
		free(last_exit);
	}
	aux->i += 2;
	aux->k++;
	return (1);
}
