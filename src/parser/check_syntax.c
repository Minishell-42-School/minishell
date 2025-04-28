/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:07:16 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/04/28 18:12:52 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_syntax(t_parser_state *token)
{
	t_parser_state	temp;
	
	temp = *token;
	if (temp.current->type == PIPE)
		ft_error("minishell: syntax error near unexpected token `|'");
	while (temp.current->type != PIPE)
		temp.current = temp.current->next;
	if (temp.current->next->type == PIPE)
		ft_error("minishell: syntax error near unexpected token `|'");
}
