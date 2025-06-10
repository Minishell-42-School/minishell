/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:12:26 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/10 14:30:51 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_all_assignments(t_command *cmd)
{
	int	i;

	if (!cmd || cmd->args_count < 1)
		return (0);
	i = 0;
	while (i < cmd->args_count)
	{
		if (!ft_strchr(cmd->args[i], '='))
			return (0);
		i++;
	}
	return (1);
}

static int	try_set_local_var(t_command *cmd, t_var **vars)
{
	char	*key;
	char	*value;
	int		i;

	if (cmd->next || !is_all_assignments(cmd))
		return (0);
	i = 0;
	while (i < cmd->args_count)
	{
		if (split_env(cmd->args[i], &key, &value) < 0)
			return (-1);
		if (!is_valid_identifier(key))
		{
			free(key);
			free(value);
			return (1);
		}
		if (vars_set(vars, key, value, 0) < 0)
			return (-1);
		free(key);
		free(value);
		i++;
	}
	return (1);
}

int	exec_set_local_vars(t_shell *shell)
{
	if (try_set_local_var(shell->cmd, &shell->vars) == 1)
	{
		free_loop(&shell->token_list, &shell->cmd);
		return (1);
	}
	return (0);
}

int	is_valid_identifier(char *key)
{
	int	i;

	if (!key || !ft_isalpha(key[0]))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
