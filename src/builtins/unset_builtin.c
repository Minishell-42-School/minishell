/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:36:44 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/23 12:26:46 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	unset_var(char *key, t_var **vars)
{
	t_var	*curr;
	t_var	*prev;

	if (!vars || !key)
		return (-1);
	curr = *vars;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(key, curr->key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*vars = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

int	unset_builtin(t_command *cmd, t_var **vars)
{
	int	i;

	i = 1;
	if (!cmd || !vars || cmd->args_count < 2)
		return (1);
	while (cmd->args[i])
	{
		unset_var(cmd->args[i], vars);
		i++;
	}
	return (0);
}
