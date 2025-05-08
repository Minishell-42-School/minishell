/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:02 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/08 14:06:54 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt(void)
{
	char	*input;

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
