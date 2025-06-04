/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:12:03 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/04 17:18:49 by ekeller-@st      ###   ########.fr       */
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

static int	check_var_assignment(t_command *cmd, t_var **vars, int *i, int *ex)
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
				*ex = 1;
			}
			else
				vars_set(vars, key, value, 1);
			free(key);
			free(value);
		}
		(*i)++;
		return (1);
	}
	return (0);
}

static int	export_builtin(t_command *cmd, t_var **vars)
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
				printf ("bash: export: `%s': not a valid identifier\n", cmd->args[i]);
				exit = 1;
			}	
			var_mark_exported(vars, cmd->args[i]);	
		}
		i++;
	}
	return (exit);
}

int	exec_export_builtin(t_shell	*s, t_command *cmd)
{
	var_to_envp(s);
	if (export_builtin(cmd, &s->vars) == 0)
		return (0);
	return (1);
}
