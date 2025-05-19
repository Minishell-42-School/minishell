/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:04:27 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/19 15:06:37 by ekeller-@st      ###   ########.fr       */
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

	token_list = NULL;
	cmd_pipeline = NULL;
	vars = NULL;
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
			if (cmd_pipeline)
				exec_cmd(cmd_pipeline);
		}
		free_all(&token_list, &cmd_pipeline);
		free(line);
	}
	free_vars(vars);
	return (0);
}
