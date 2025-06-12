/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:07:16 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/12 14:11:39 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// check if first command starts with pipe and if there
//are two pipes in a sequence.
int	check_syntax(t_parser_state *token)
{
	t_parser_state	temp;

	if (!token || !token->current)
		return (0);
	temp = *token;
	if (temp.current && temp.current->type == PIPE)
	{
		ft_printf_stderr(" syntax error near unexpected token `|'\n");
		return (1);
	}
	while (temp.current && temp.current->type != PIPE)
		temp.current = temp.current->next;
	if (!temp.current)
		return (0);
	if (temp.current->next && temp.current->next->type == PIPE)
	{
		ft_printf_stderr(" syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

void	ft_error(t_shell *shell, char *msg)
{
	printf("%s", msg);
	free_all(shell, EXIT_FAILURE);
}
