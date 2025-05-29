/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:16:18 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/29 12:47:40 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

void	heredoc_signals(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ign_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	g_exit_status = 130;
	printf("\n");
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
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
