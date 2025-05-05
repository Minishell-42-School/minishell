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

int	main(void)
{
	char *args1[] = {"ls", NULL, NULL};
	char *args2[] = {"wc", "-l", NULL};
	char *args3[] = {"echo", "Hello World", NULL};
  char *args4[] = {"tr", "a-z", "A-Z", NULL};
  // Multiplos pipes:
  char *args5[] = {"cat", "/etc/passwd", NULL};
  char *args6[] = {"head", "-n", "3", NULL};
  char *args7[] = {"wc", "-l", NULL};

//   t_command *cmd1 = make_cmd("ls", args1);
	// t_command *cmd2 = make_cmd("wc", args2);
	t_command *cmd3 = make_cmd("echo", args3);
  t_command *cmd4 = make_cmd("tr", args4);
//   t_command *cmd5 = make_cmd("cat", args5);
//   t_command *cmd6 = make_cmd("head", args6);
  // t_command *cmd7 = make_cmd("wc", args7);
	// cmd1->next = cmd2;
	// cmd2->next = cmd3;
  cmd3->next = cmd4;
  // cmd4->next = cmd5;
//   cmd5->next = cmd6;
  // cmd6->next = cmd7;

//   exec_pipeline(cmd1);
  // printf("\n\n --------------- \n\n");
	exec_pipeline(cmd3);
  // printf("\n\n --------------- \n\n");
  // exec_pipeline(cmd5);

	// free(cmd1);
	// free(cmd2);
	free(cmd3);
  free(cmd4);
//   free(cmd5);
//   free(cmd6);
  // free(cmd7);
	return 0;
}
