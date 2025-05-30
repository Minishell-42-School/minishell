/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:02:54 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/30 16:38:58 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

void	init_t_shell(t_shell *shell)
{
	shell->cmd = NULL;
	shell->token_list = NULL;
	shell->vars = NULL;
	shell->new_envp = NULL;
}

int	main(int argc, char **av, char **envp)
{
	t_shell			shell;
	//check flags in make
	if (argc || av)
		;
	init_t_shell(&shell);
	init_vars_from_envp(&shell.vars, envp);
	var_to_envp(&shell);
	while (1)
	{
		shell.line = get_prompt();
		if (!shell.line)
			break ;
		get_token(&shell.token_list, shell.line);
		free(shell.line);
		expand_all_tokens(shell.token_list, shell.vars);
		if (shell.token_list)
		{
			shell.p_state.current = shell.token_list;
			shell.cmd = parse_pipeline(&shell.p_state);
			if (exec_set_local_vars(&shell) == 1)
				continue ;
			if (shell.cmd)
				exec_cmd(&shell);
			free_loop(&shell.token_list, &shell.cmd);
		}
	}
	free_vars_and_envp(shell.vars, shell.new_envp);
	return (0);
}
