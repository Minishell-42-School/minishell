/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:02 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/08 15:43:11 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_exit_signal;

char	*get_prompt(void)
{
	char	*input;

  // if (g_exit_signal == 130)
	// {
    // printf("Prompt.. %d\n", g_exit_signal);
	// 	g_exit_signal = 0;
	// 	return (NULL);
	// }
	config_signals();
	input = readline(GREEN"Minishell~> "RESET);
	if (!input)
	{
		printf("%s...Exit Minishell...\n%s", YELLOW, RESET);
		rl_clear_history();
		exit(0);
	}
	if (*input)
		add_history(input);
	return (input);
}
