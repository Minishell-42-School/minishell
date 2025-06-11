/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:51:51 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/03 11:21:13 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(t_shell *shell, int status)
{
	free_loop(&shell->token_list, &shell->cmd);
	free_vars_and_envp(shell->vars, shell->new_envp);
	rl_clear_history();
  if (status != -42)
	  exit(status);
}
