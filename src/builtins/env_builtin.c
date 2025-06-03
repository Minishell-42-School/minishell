/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:54:28 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/03 17:17:53 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_env_builtin(t_shell *s, t_command *cmd)
{
	t_var	*v;

	v = s->vars;
	if (cmd->args_count == 1)
	{
		while (v)
		{
			if (v->exported == 1)
				printf("%s=%s\n", v->key, v->value);
			v = v->next;
		}
	}
	else
		printf("env error");
	return (0);
}
