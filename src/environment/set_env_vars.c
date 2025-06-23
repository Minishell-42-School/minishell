/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:43:19 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/23 13:25:07 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_vars_from_envp(t_var **vars, char **envp)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		if (split_env(envp[i], &key, &value) == 0)
		{
			if (vars_set(vars, key, value, 1) < 0)
			{
				free(key);
				free(value);
				return (-1);
			}
		}
		free(key);
		free(value);
		i++;
	}
	return (0);
}

int	vars_set(t_var **vars, char *key, char *value, int exported)
{
	t_var	*v;

	v = var_find(*vars, key);
	if (v)
	{
		free(v->value);
		v->value = strdup(value);
		v->exported |= exported;
		return (0);
	}
	v = malloc(sizeof(*v));
	if (!v)
		return (-1);
	v->key = strdup(key);
	v->value = strdup(value);
	v->exported = exported;
	v->print = 0;
	v->next = *vars;
	*vars = v;
	return (0);
}

t_var	*var_find(t_var *vars, const char *key)
{
	while (vars)
	{
		if (ft_strcmp(key, vars->key) == 0)
			return (vars);
		vars = vars->next;
	}
	return (NULL);
}

int	split_env(const char *env, char **key, char **value)
{
	char	*equal;
	size_t	len;

	equal = ft_strchr(env, '=');
	if (!equal)
		return (-1);
	*value = ft_strdup(equal + 1);
	if (!*value)
		return (-1);
	len = (size_t)(equal - env);
	*key = malloc(len + 1);
	ft_memcpy(*key, env, len);
	if (!*key)
	{
		free(*value);
		return (-1);
	}
	(*key)[len] = '\0';
	return (0);
}

char	*var_get(t_var *vars, const char *key)
{
	t_var	*v;

	v = var_find(vars, key);
	if (v)
		return (v->value);
	else
		return (NULL);
}
