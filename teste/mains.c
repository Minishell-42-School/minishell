// #include "../includes/minishell.h"

// // Teste token

// int	main(void)
// {
// 	char	*line;
// 	t_token	*token_list;

// 	token_list = NULL;
// 	while (1)
// 	{
// 		line = get_prompt();
// 		if (!line)
// 			break ;
// 		printf("Recebido: %s\n", line);
// 		get_token(&token_list, line);

// 		t_token	*tmp;
// 		tmp = token_list;
// 		int x = 0;
// 		while (tmp)
// 		{
// 			if (tmp->nbr_env_var > 0)
// 			{
// 				int i = 0;
// 				while (i < tmp->nbr_env_var)
// 				{
// 					printf("..Token %d: \ntype - %d | n_env %d -> Exp %d\n%s%s%s\n\n", x, tmp->type, tmp->nbr_env_var, tmp->expand_var[i], GREEN, tmp->value, RESET);
// 					i++;
// 				}
// 			}
// 			else if (tmp->value[0] == '\0')
// 				printf("..Token %d: \ntype %d | String vazia %s%s%s\n\n", x, tmp->type, GREEN, tmp->value, RESET);
// 			else
// 					printf("..Token %d: \ntype - %d | n_env %d | %s%s%s\n\n", x, tmp->type, tmp->nbr_env_var, GREEN, tmp->value, RESET);
// 			x++;
// 			tmp = tmp->next;
// 		}
// 		clean_all(&token_list);
// 		free(line);
// 	}
// 	return (0);
// }

// ---------------------------------------

// Teste Parse
// int	main(void)
// {
// 	char			*line;
// 	t_token			*token_list;
// 	t_command		*cmd_pipeline;
// 	t_command   	*cmd;
// 	t_parser_state	p_state;
// 	int 			cmd_num;
// 	t_redirections  *redir;

// 	token_list = NULL;
// 	while (1)
// 	{
// 		line = get_prompt();
// 		if (!line)
// 			break ;
// 		printf("Recebido: %s\n", line);
// 		get_token(&token_list, line);
// 		// exec_external_cmd(cmd);

// 		p_state.current = token_list;
// 		cmd_pipeline = parse_pipeline(&p_state);
// 		if (!cmd_pipeline)
// 		{
// 			clean_all(&token_list);
// 			free(line);
// 			continue;
// 		}
// 		cmd = cmd_pipeline;
// 		cmd_num = 1;
// 		while (cmd != NULL)
// 		{
// 			printf("Command %d:\n", cmd_num);
// 			printf("  Command name: %s\n", cmd->command_name);
// 			printf("  Arguments (%d): ", cmd->args_count);
// 			for (int i = 0; i < cmd->args_count; i++)
// 				printf("%s ", cmd->args[i]);
// 			printf("\n");
// 			redir = cmd->redirs;
// 			while (redir)
// 			{
// 				if (redir->type == 0)
// 					printf("Redir type: %c / file name: %s\n", '<', redir->filename);
// 				if (redir->type == 1)
// 					printf("Redir type: %c / file name: %s\n", '>', redir->filename);
// 				if (redir->type == 2)
// 					printf("Redir type: %s / file name: %s\n", "<<", redir->filename);
// 				if (redir->type == 3)
// 					printf("Redir type: %s / file name: %s\n", ">>", redir->filename);
// 				redir = redir->next;
// 			}
// 			printf("\n");
// 			cmd = cmd->next;
// 			cmd_num++;
// 		}
// 		clean_all(&token_list);
// 		free(line);
// 		free_command_list(cmd_pipeline);
// 	}
// 	return (0);
// }

// ------------------------------------------------------
// Testes Comandos externos

// t_command	*make_cmd(char *name, char **args)
// {
// 	t_command *cmd = malloc(sizeof(t_command));
// 	cmd->command_name = name;
// 	cmd->args = args;
// 	cmd->args_count = 0;
// 	cmd->redirs = NULL;
// 	cmd->nbr_env_var = 0;
// 	cmd->expand_var = NULL;
// 	cmd->next = NULL;
// 	return cmd;
// }

// int	main(void)
// {
// 	char *args1[] = {"ls", NULL, NULL};
// 	char *args2[] = {"cat", "lib.c", NULL};
// 	char *args3[] = {"ls", "-l", NULL};
//   char *args4[] = {"wc", "-l", "/etc/passwd", NULL};
//   char *args5[] = {"/bin/ls", NULL, NULL};

// 	t_command *cmd1 = make_cmd("ls", args1);
// 	t_command *cmd2 = make_cmd("cat", args2);
// 	t_command *cmd3 = make_cmd("ls", args3);
//   t_command *cmd4 = make_cmd("wc", args4);
//   t_command *cmd5 = make_cmd("/bin/ls", args5);
// 	cmd1->next = cmd2;
// 	cmd2->next = cmd3;
//   cmd3->next = cmd4;
//   cmd4->next = cmd5;

// 	exec_cmd_ext(cmd1);
//   printf("\n\n --------------- \n\n");
//   exec_cmd_ext(cmd2);
//   printf("\n\n --------------- \n\n");
//   exec_cmd_ext(cmd3);
//   printf("\n\n --------------- \n\n");
//   exec_cmd_ext(cmd4);
//   printf("\n\n --------------- \n\n");
//   exec_cmd_ext(cmd5);

// 	free(cmd1);
// 	free(cmd2);
// 	free(cmd3);
//   free(cmd4);
//   free(cmd5);
// 	return 0;
// }

// -----------------------------------------

// Testes Pipe

// t_command	*make_cmd(char *name, char **args)
// {
// 	t_command *cmd = malloc(sizeof(t_command));
// 	cmd->command_name = name;
// 	cmd->args = args;
// 	cmd->args_count = 0;
// 	cmd->redirs = NULL;
// 	cmd->nbr_env_var = 0;
// 	cmd->expand_var = NULL;
// 	cmd->next = NULL;
// 	return cmd;
// }

// int	main(void)
// {
// 	char *args1[] = {"ls", NULL, NULL};
// 	char *args2[] = {"wc", "-l", NULL};
// 	char *args3[] = {"echo", "Hello World", NULL};
//   char *args4[] = {"tr", "a-z", "A-Z", NULL};
//   // Multiplos pipes:
//   char *args5[] = {"grep", ".c", NULL};

//   char *args8[] = {"cat", "/etc/passwd", NULL};
//   char *args9[] = {"head", "-n", "3", NULL};

//   t_command *cmd1 = make_cmd("ls", args1);
// 	t_command *cmd2 = make_cmd("wc", args2);

// 	t_command *cmd3 = make_cmd("echo", args3);
//   t_command *cmd4 = make_cmd("tr", args4);

//   t_command *cmd5 = make_cmd("ls", args1);
//   t_command *cmd6 = make_cmd("grep", args5);
//   t_command *cmd7 = make_cmd("wc", args2);

//   t_command *cmd8 = make_cmd("cat", args8);
//   t_command *cmd9 = make_cmd("head", args9);
//   t_command *cmd10 = make_cmd("wc", args2);

// 	cmd1->next = cmd2;
//   cmd3->next = cmd4;
//   cmd5->next = cmd6;
//   cmd6->next = cmd7;
//   cmd8->next = cmd9;
//   cmd9->next = cmd10;

//   exec_pipeline(cmd1);
//   printf("\n --------------- \n\n");
// 	exec_pipeline(cmd3);
//   printf("\n --------------- \n\n");
//   exec_pipeline(cmd5);
//   printf("\n --------------- \n\n");
//   exec_pipeline(cmd8);

// 	free(cmd1);
// 	free(cmd2);
// 	free(cmd3);
//   free(cmd4);
//   free(cmd5);
//   free(cmd6);
//   free(cmd7);
//   free(cmd8);
//   free(cmd9);
//   free(cmd10);
// 	return 0;
// }
