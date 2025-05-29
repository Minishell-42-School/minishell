/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:47:28 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/29 17:06:16 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_echo_builtin(t_shell *s)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (s->cmd->args[1] && ft_strcmp(s->cmd->args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (s->cmd->args[i])
	{
		printf("%s", s->cmd->args[i]);
		if (s->cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
