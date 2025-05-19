/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:10:45 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/19 11:20:15 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **av, char **envp)
{
	char			*line;
	t_token			*token_list;
	t_command		*cmd_pipeline;
	t_command   	*cmd;
	t_parser_state	p_state;
	int 			cmd_num;
	t_redirections  *redir;
	t_var			*vars;
	
	vars = NULL;
	if (init_vars_from_envp(&vars, envp) < 0)
		return (1);
	if (argc)
		;
	if (av)
		;
	token_list = NULL;
	while (1)
	{
		line = get_prompt();
		if (!line)
			break ;
		printf("Recebido: %s\n", line);
		get_token(&token_list, line);
		expand_all_tokens(token_list, vars);

		p_state.current = token_list;
		cmd_pipeline = parse_pipeline(&p_state);
		if (!cmd_pipeline)
		{
			free_token_lst(&token_list);
			free(line);
			continue;
		}
		cmd = cmd_pipeline;
		cmd_num = 1;
		while (cmd != NULL)
		{
			printf("Command %d:\n", cmd_num);
			printf("  Command name: %s\n", cmd->command_name);
			printf("  Arguments (%d): ", cmd->args_count);
			for (int i = 0; i < cmd->args_count; i++)
				printf("%s ", cmd->args[i]);
			printf("\n");	
			redir = cmd->redirs;
			while (redir)
			{
				if (redir->type == 0)
					printf("Redir type: %c / file name: %s\n", '<', redir->filename);
				if (redir->type == 1)
					printf("Redir type: %c / file name: %s\n", '>', redir->filename);
				if (redir->type == 2)
					printf("Redir type: %s / file name: %s\n", "<<", redir->filename);
				if (redir->type == 3)
					printf("Redir type: %s / file name: %s\n", ">>", redir->filename);            
				redir = redir->next; 
			}
			printf("\n");
			cmd = cmd->next;
			cmd_num++;
		}
		free_token_lst(&token_list);
		free(line);
		free_command_list(cmd_pipeline);
	}
	free_vars(vars);
	return (0);
}
