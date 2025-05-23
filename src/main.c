/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:04:27 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/23 10:31:23 by ekeller-@st      ###   ########.fr       */
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
	//t_var			*export_test;

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
			// export_builtin(cmd_pipeline, &vars);
			// export_test = var_find(vars, "v1");
			// printf("%s=%s\n%i\n", export_test->key, export_test->value, export_test->exported);
			//use new_envp somewhere in execv() during execution.
			//need to check creation in case of "export";
			new_envp = var_to_envp(vars); 
			if (cmd_pipeline)
			 	exec_cmd(cmd_pipeline);
		}
		free_all(&token_list, &cmd_pipeline, new_envp);
		new_envp = NULL;
		free(line);
	}
	free_vars(vars);
	return (0);
}
