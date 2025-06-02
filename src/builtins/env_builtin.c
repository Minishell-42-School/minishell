/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:54:28 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/02 12:49:22 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_env_builtin(t_shell *s)
{
	t_var	*v;

	v = s->vars;
	if (s->cmd->args_count == 1)
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
