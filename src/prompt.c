/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:02 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/11 17:41:27 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt(t_shell *shell)
{
	char	*input;

	config_signals();
	input = readline(GREEN"Minishell~> "RESET);
	if (!input)
	{
		printf("%s...Exit Minishell...\n%s", YELLOW, RESET);
		free_all(shell, 0);
	}
	if (*input)
		add_history(input);
	return (input);
}
