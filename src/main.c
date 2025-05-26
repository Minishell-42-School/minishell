/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:04:27 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/26 18:38:12 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_t_shell(t_shell *shell)
{
	shell->cmd_pipeline = NULL;
	shell->token_list = NULL;
	shell->vars = NULL;
	shell->new_envp = NULL;
}



int	main(int argc, char **av, char **envp)
{
	t_shell			shell;
	
	init_t_shell(&shell);
	if (argc || av)
		;
	if (init_vars_from_envp(&shell.vars, envp) < 0)
		return (1);
	while (1)
	{
		shell.line = get_prompt();
		if (!shell.line)
			break ;
		get_token(&shell.token_list, shell.line);
		expand_all_tokens(shell.token_list, shell.vars);
		if (shell.token_list)
		{
			shell.p_state.current = shell.token_list;
			shell.cmd = parse_pipeline(&shell.p_state);
			if (try_set_local_var(shell.cmd, &shell.vars) == 1)
			{
				free_all(&shell.token_list, &shell.cmd, shell.new_envp);
				shell.new_envp = NULL;
				free(shell.line);
				continue;
			}
			//use new_envp somewhere in execv() during execution.
			//need to check creation in case of "export";
			shell.new_envp = var_to_envp(shell.vars); 
			if (shell.cmd)
			 	exec_cmd(&shell);
		}
		free_all(&shell.token_list, &shell.cmd, shell.new_envp);
		shell.new_envp = NULL;
		free(shell.line);
	}
	free_vars(shell.vars);
	return (0);
}
