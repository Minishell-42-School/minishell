/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:16:18 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/08 15:43:06 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

static void	handle_sigin(int sig)
{
	(void)sig;
	g_signal = 100;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	config_signals(void)
{
	signal(SIGINT, handle_sigin);
	signal(SIGQUIT, SIG_IGN);
}
