/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:02 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/10 16:32:19 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt(t_shell *shell)
{
	char	*input;

	config_signals();
	input = readline(GREEN"Minishell~> "RESET);
	if (g_signal)
	{
		shell->last_status = 130;
		g_signal = 0;
	}
	if (!input)
	{
		printf("%s...Exit Minishell...\n%s", YELLOW, RESET);
		return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}
