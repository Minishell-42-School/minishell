/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:23:56 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/12 18:25:12 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_get(t_var *vars, const char *key)
{
	t_var *v;

	v = var_find(vars, key);
	if (v)
		return (v->value);
	else
		return (NULL);
}

//what happens if there is out of bounds access in "tok->expand_var[k]"?
size_t	calc_new_len(t_token *tok, t_var *vars)
{
	int		i;
	int		k;
	int		var_len;
	size_t	len;
	char	*new_value;

	i = 0;
	k = 0;
	while (tok->value[i])
	{
		if(tok->expand_var && tok->expand_var[k] && tok->value[i] == '$')
			process_env_flags(tok, &i, &k, &len, vars);
		else
		{
			len++;
			if (tok->expand_var && !tok->expand_var[k] && tok->value[i] == '$')
				k++;
			i++;
		}
	}
	return (len);
}

void	process_env_flags(t_token *tok, int *i, int *k, size_t *len, t_var *vars)
{
	char	*new_value;
	
	new_value = var_get(vars, tok->value + *i + 1);
	if (new_value)
		len += ft_strlen(new_value);
	i += var_name_len(tok->value + *i + 1) + 1;
	(*k)++;
}

int	var_name_len(char *tok_val)
{
	int	len;

	len = 0;
	while ((tok_val[len] >= 'A' && tok_val[len] <= 'Z') ||
			(tok_val[len] >= 'a' && tok_val[len] <= 'z') ||
			(tok_val[len] >= '0' && tok_val[len] <= '9') ||
			tok_val[len] == '_')
		len++;
	return (len);
}