/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_looping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:10:45 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/04 12:15:01 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_looping(t_shell *shell)
{
	while (1)
	{
		shell->line = get_prompt(shell);
		if (!shell->line)
			break ;
		get_token(&shell->token_list, shell->line);
		free(shell->line);
		expand_all_tokens(shell->token_list, shell->vars);
		if (shell->token_list)
		{
			shell->p_state.current = shell->token_list;
			shell->cmd = parse_pipeline(&shell->p_state);
			if (exec_set_local_vars(shell) == 1)
				continue ;
			if (shell->cmd)
				exec_cmd(shell);
			free_loop(&shell->token_list, &shell->cmd);
		}
	}
}
