/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:51:51 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/12 18:03:29 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(t_shell *shell, int status)
{
	if (shell->interactive)
		tcsetattr(STDIN_FILENO, TCSANOW, &shell->term_backup);
	free_loop(shell);
	free_vars_and_envp(shell->vars, shell->new_envp);
	if (shell->hdoc_file && shell->hdoc_control)
		free(shell->hdoc_file);
	rl_clear_history();
	exit(status);
}
