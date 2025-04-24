/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:02 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/17 16:05:52 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt(void)
{
	char	*input;

	input = readline(GREEN"Minishell~> "RESET);
	// Ctrl+D
	if (!input)
	{
		printf("%s...Exit Minishell...\n%s", YELLOW, RESET);
		exit(0);
	}
	if (*input)
		add_history(input);
	return (input);
}
