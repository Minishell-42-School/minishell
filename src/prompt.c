/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:02 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/22 18:10:11 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	g_exit_signal;

char	*get_prompt(void)
{
	char	*input;

	config_signals();
	// printf("signal-> %d\n", g_exit_signal);
	// if (g_exit_signal == 130)
	// {
	// 	// printf("AKII\n");
	// 	input = malloc(1 * sizeof(char));
	// 	input[0] = '\0';
	// 	g_exit_signal = 0;
	// }
	// else
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
