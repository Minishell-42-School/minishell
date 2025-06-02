/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:10:45 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/02 12:33:15 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **av, char **envp)
{
	char			*line;
	t_token			*token_list;
	t_command		*cmd_pipeline;
	t_parser_state	p_state;
	t_var			*vars;
	char			**new_envp;

	token_list = NULL;
	cmd_pipeline = NULL;
	vars = NULL;
	new_envp = NULL;
	if (argc || av)
		;
	if (init_vars_from_envp(&vars, envp) < 0)
		return (1);
	while (1)
	{
		line = get_prompt();
		if (!line)
			break ;
		get_token(&token_list, line);
		free(line);
		expand_all_tokens(token_list, vars);
		if (token_list)
		{
			p_state.current = token_list;
			cmd_pipeline = parse_pipeline(&p_state);
			if (try_set_local_var(cmd_pipeline, &vars) == 1)
			{
				free_all(&token_list, &cmd_pipeline, new_envp);
				new_envp = NULL;
				free(line);
				continue;
			}
			//use new_envp somewhere in execv() during execution.
			//need to check creation in case of "export";
			new_envp = var_to_envp(vars); 
			if (cmd_pipeline)
				exec_cmd(cmd_pipeline);
		}
		free_all(&token_list, &cmd_pipeline, new_envp);
		new_envp = NULL;
		// free(line);
	}
	free_vars(vars);
	return (0);
}
