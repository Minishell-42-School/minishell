/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:12:03 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/03 10:12:06 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	var_mark_exported(t_var **vars, char *arg)
{
	t_var	*export;

	export = var_find(*vars, arg);
	if (export)
		export->exported = 1;
}

static int	check_var_assignment(t_command *cmd, t_var **vars, int *i)
{
	char	*key;
	char	*value;

	if (ft_strchr(cmd->args[*i], '='))
	{
		if (split_env(cmd->args[*i], &key, &value) == 0)
		{
			if (!is_valid_identifier(key))
			{
				printf("bash: export: `%s=%s' : not a valid identifier\n",
					key, value);
				free(key);
				free(value);
			}
			else
			{
				vars_set(vars, key, value, 1);
				free(key);
				free(value);
			}
		}
		(*i)++;
		return (1);
	}
	return (0);
}

static int	export_builtin(t_command *cmd, t_var **vars)
{
	int		i;

	i = 1;
	if (cmd->args_count == 1)
		return (print_sorted_export(*vars));
	while (cmd->args[i])
	{
		if (check_var_assignment(cmd, vars, &i) == 1)
			continue ;
		else
			var_mark_exported(vars, cmd->args[i]);
		i++;
	}
	return (0);
}

int	exec_export_builtin(t_shell	*s)
{
	if (export_builtin(s->cmd, &s->vars) == 0)
	{
		var_to_envp(s);
		return (0);
	}
	return (0);
}
