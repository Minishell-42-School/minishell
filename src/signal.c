/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:16:18 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/22 18:09:20 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	// g_exit_signal = 130;
}

// void	config_signals(void)
// {
// 	struct sigaction sa;

// 	sa.sa_handler = handle_sigint;
// 	// sa.sa_flags = SA_RESTART;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }


// void	handle_sigin(int sig)
// {
// 	(void)sig;
// 	// if (g_exit_signal == 1)
// 	// 	write(STDERR_FILENO, "\n", 1);
// 	// else
// 	// {
// 		printf("\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		g_exit_signal = 130;
// 	// }
// }

// // static void	handle_exit(int sig)
// // {
// // 	(void)sig;
// 	// if (g_exit_signal == 1)
// 	// 	write(STDERR_FILENO, "\n", 1);
// 	// else
// 	// {
// 		// printf("oiiii\n");
// 		// rl_replace_line("", 0);
// 		// rl_on_new_line();
// 		// rl_redisplay();
// 	// 	g_exit_signal = 130;
// 	// }
// // }

void	config_signals()
{
	// if (g_exit_signal == 130)
	// 	signal(SIGINT, handle_exit);
	// else
		signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
