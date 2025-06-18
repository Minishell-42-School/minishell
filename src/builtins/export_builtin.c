/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:12:03 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/18 17:34:52 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	var_mark_exported(t_var **vars, char *arg)
{
	t_var	*export;

	export = var_find(*vars, arg);
	if (export)
		export->exported = 1;
	else
	{
		vars_set(vars, arg, "", 1);
		export = var_find(*vars, arg);
	}
	export->print = 1;
}

static void	handle_split(t_command *cmd, t_var **vars, int *i, int *ex)
{
	char	*key;
	char	*value;
	t_var	*export;

	if (split_env(cmd->args[(*i)], &key, &value) == 0)
	{
		if (!is_valid_identifier(key))
		{
			printf_stderr("bash: export: `%s=%s' : not a valid identifier\n",
				key, value);
			*ex = 1;
		}
		else
		{
			vars_set(vars, key, value, 1);
			export = var_find(*vars, key);
			export->print = 0;
		}
		free(key);
		free(value);
	}
	(*i)++;
}

static int	check_var_assignment(t_command *cmd, t_var **vars, int *i, int *ex)
{
	if (ft_strchr(cmd->args[(*i)], '='))
	{
		handle_split(cmd, vars, i, ex);
		return (1);
	}
	return (0);
}

int	export_builtin(t_command *cmd, t_var **vars)
{
	int		i;
	int		exit;

	exit = 0;
	i = 1;
	if (cmd->args_count == 1)
		return (print_sorted_export(*vars));
	while (cmd->args[i])
	{
		if (check_var_assignment(cmd, vars, &i, &exit) == 1)
			continue ;
		else
		{
			if (is_valid_identifier(cmd->args[i]) == 0)
			{
				printf_stderr("bash: export: `%s': not a valid identifier\n",
					cmd->args[i]);
				exit = 1;
			}
			else
				var_mark_exported(vars, cmd->args[i]);
		}
		i++;
	}
	return (exit);
}

int	exec_export_builtin(t_shell	*s, t_command *cmd)
{
	int	result;
	
	result = export_builtin(cmd, &s->vars);
	var_to_envp(s);
	return (result);
}
