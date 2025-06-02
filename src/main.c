/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:02:54 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/02 16:54:18 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_t_shell(t_shell *shell)
{
	shell->cmd = NULL;
	shell->token_list = NULL;
	shell->vars = NULL;
	shell->new_envp = NULL;
}

// int	main(int argc, char **av, char **envp)
// {
// 	t_shell			shell;
// 	//check flags in make
// 	if (argc || av)
// 		;
// 	init_t_shell(&shell);
// 	init_vars_from_envp(&shell.vars, envp);
// 	var_to_envp(&shell);
// 	while (1)
// 	{
// 		shell.line = get_prompt();
// 		if (!shell.line)
// 			break ;
// 		get_token(&shell.token_list, shell.line);
// 		free(shell.line);
// 		expand_all_tokens(shell.token_list, shell.vars);
// 		if (shell.token_list)
// 		{
// 			shell.p_state.current = shell.token_list;
// 			shell.cmd = parse_pipeline(&shell.p_state);
// 			if (exec_set_local_vars(&shell) == 1)
// 				continue ;
// 			if (shell.cmd)
// 				exec_cmd(&shell);
// 			free_loop(&shell.token_list, &shell.cmd);
// 		}
// 	}
// 	free_vars_and_envp(shell.vars, shell.new_envp);
// 	return (0);
// }

int	main(void)
{
	char			*line;
	t_token			*token_list;
	t_command		*cmd_pipeline;
	t_command   	*cmd;
	t_parser_state	p_state;
	int 			cmd_num;
	t_redirections  *redir;

	token_list = NULL;
	while (1)
	{
		line = get_prompt();
		if (!line)
			break ;
		printf("Recebido: %s\n", line);
		get_token(&token_list, line);

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
	return (0);
}