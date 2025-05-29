/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:54:28 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/29 17:03:50 by ekeller-@st      ###   ########.fr       */
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
			printf("%s=", v->key);
			printf("%s\n", v->value);
			v = v->next;
		}
	}
	else
		printf("env error");
	return (0);
}
