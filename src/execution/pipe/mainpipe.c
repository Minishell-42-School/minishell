#include "pipe.h"

t_command	*make_cmd(char *name, char **args)
{
	t_command *cmd = malloc(sizeof(t_command));
	cmd->command_name = name;
	cmd->args = args;
	cmd->args_count = 0;
	cmd->redirs = NULL;
	cmd->nbr_env_var = 0;
	cmd->expand_var = NULL;
	cmd->next = NULL;
	return cmd;
}

t_command	*make_cmd_red(char *name, char **args, t_redirections *redir)
{
	t_command *cmd = malloc(sizeof(t_command));
	cmd->command_name = name;
	cmd->args = args;
	cmd->args_count = 0;
	cmd->redirs = redir;
	cmd->nbr_env_var = 0;
	cmd->expand_var = NULL;
	cmd->next = NULL;
	return cmd;
}

int	main(void)
{
	char *args1[] = {"ls", NULL, NULL};
	char *args2[] = {"wc", "-l", NULL};
	char *args3[] = {"echo", "Hello World", NULL};
  char *args4[] = {"tr", "a-z", "A-Z", NULL};
  // Multiplos pipes:
  char *args5[] = {"grep", ".c", NULL};

  char *args8[] = {"cat", "/etc/passwd", NULL};
  char *args9[] = {"head", "-n", "3", NULL};

  // Pipe with redir
  // grep "user" < entrada.txt | uniq >> saida.txt
  char *args11[] = {"grep", "user", NULL};
  t_redirections *redir1 = {R_IN, "entrada.txt", NULL};
  char *args12[] = {"uniq", NULL, NULL};
  t_redirections *redir2 = {R_DELIMITER, "saida.txt", NULL};


  t_command *cmd1 = make_cmd("ls", args1);
	t_command *cmd2 = make_cmd("wc", args2);

	t_command *cmd3 = make_cmd("echo", args3);
  t_command *cmd4 = make_cmd("tr", args4);

  t_command *cmd5 = make_cmd("ls", args1);
  t_command *cmd6 = make_cmd("grep", args5);
  t_command *cmd7 = make_cmd("wc", args2);

  t_command *cmd8 = make_cmd("cat", args8);
  t_command *cmd9 = make_cmd("head", args9);
  t_command *cmd10 = make_cmd("wc", args2);

  t_command *cmd11 = make_cmd_red("grep", args11, redir1);
  t_command *cmd12 = make_cmd_red("uniq", args12, redir2);

	cmd1->next = cmd2;
  cmd3->next = cmd4;
  cmd5->next = cmd6;
  cmd6->next = cmd7;
  cmd8->next = cmd9;
  cmd9->next = cmd10;
  cmd11->next = cmd12;

  // exec_pipeline(cmd1);
  // printf("\n --------------- \n\n");
	// exec_pipeline(cmd3);
  // printf("\n --------------- \n\n");
  // exec_pipeline(cmd5);
  // printf("\n --------------- \n\n");
  // exec_pipeline(cmd8);
  printf("\n --------------- \n\n");
  exec_pipeline(cmd11);

	free(cmd1);
	free(cmd2);
	free(cmd3);
  free(cmd4);
  free(cmd5);
  free(cmd6);
  free(cmd7);
  free(cmd8);
  free(cmd9);
  free(cmd10);
  free(cmd11);
  free(cmd12);
	return 0;
}
