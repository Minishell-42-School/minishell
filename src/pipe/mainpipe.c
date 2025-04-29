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
	char *args1[] = {"echo", "Hello World", NULL};
	char *args2[] = {"grep", "Hello", NULL};
	char *args3[] = {"wc", "-l", NULL};

	t_command *cmd1 = make_cmd("echo", args1);
	t_command *cmd2 = make_cmd("grep", args2);
	t_command *cmd3 = make_cmd("wc", args3);
	cmd1->next = cmd2;
	cmd2->next = cmd3;

	exec_pipeline(cmd1);

	free(cmd1);
	free(cmd2);
	free(cmd3);
	return 0;
}
