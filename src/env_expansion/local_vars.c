/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:41:03 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/21 14:13:04 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	try_set_local_var(t_command *cmd_pipeline, t_var **vars)
{
	char	*key;
	char	*value;

	if (cmd_pipeline->next != NULL || cmd_pipeline->args_count != 1)
		return (0);
	if (ft_strchr(cmd_pipeline->args[0], '=') == NULL)
		return (0);
	if (split_env(cmd_pipeline->args[0], &key, &value) < 0)
		return (-1);
	if (vars_set(vars, key, value, 0) < 0)
	{
		free(key);
		free(value);
		return (-1);
	}
	free(key);
	free(value);
	return (1);
}
