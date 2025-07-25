/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_looping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:10:45 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/23 13:37:17 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	verify_empty_arg0(t_shell *s)
{
	int	i;

	i = 0;
	if (!s->cmd->args[0])
		return (0);
	if ((ft_strcmp(s->cmd->args[0], "") == 0) && !s->cmd->args[1])
	{
		free_loop(s);
		return (1);
	}
	else if ((ft_strcmp(s->cmd->args[0], "") == 0) && s->cmd->args[1])
	{
		free (s->cmd->args[0]);
		while (s->cmd->args[i + 1])
		{
			s->cmd->args[i] = s->cmd->args[i + 1];
			i++;
		}
		s->cmd->args[i] = NULL;
		free(s->cmd->command_name);
		s->cmd->command_name = ft_strdup(s->cmd->args[0]);
	}
	return (0);
}

void	parse_and_exec(t_shell *shell)
{
	int	verif_error;

	verif_error = 0;
	shell->p_state.current = shell->token_list;
	shell->cmd = parse_pipeline(&verif_error, &shell->p_state);
	if (verif_error)
	{
		if (verif_error == 127)
			shell->last_status = 127;
		else
			shell->last_status = 2;
		free_loop(shell);
		return ;
	}
	if (verify_empty_arg0(shell) == 1)
		return ;
	if (exec_set_local_vars(shell) == 1)
		return ;
	if (shell->cmd)
		exec_cmd(shell);
	free_loop(shell);
}

void	main_looping(t_shell *shell)
{
	int	verif_error;

	verif_error = 0;
	while (1)
	{
		shell->line = get_prompt(shell);
		if (!shell->line)
			break ;
		verif_error = get_token(&shell->token_list, shell->line);
		if (verif_error)
			shell->last_status = 2;
		free(shell->line);
		expand_all_tokens(shell);
		if (shell->token_list)
			parse_and_exec(shell);
	}
}
