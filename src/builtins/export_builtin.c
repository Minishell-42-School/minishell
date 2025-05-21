/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:06:36 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/21 17:34:29 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//does not sort
static int	export_print(t_var *vars)
{
	t_var	*tmp;

	tmp = vars;
	while (tmp)
	{
		if (tmp->exported)
		{
			if (tmp->value)
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			else
				printf("declare -x %s\n", tmp->key);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	var_mark_exported(t_var *vars, char *arg)
{
	t_var	*export;
	
	export = var_find(vars, arg);
	if (export)
		export->exported = 1;
}

void	export_builtin(t_command *cmd, t_var *vars)
{
	int		i;
	char	*key;
	char	*value;

	
	i = 1;
	if (cmd->args_count == 1)
		return (export_print(vars));
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '='))
		{
			if (split_env(cmd->args[i], &key, &value) == 0)
			{
				vars_set(&vars, key, value, 1);
				free(key);
				free(value);
			}
		}
		else
			var_mark_exported(vars, cmd->args[i]);
		i++;
	}
}
