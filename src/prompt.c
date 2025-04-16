#include "../includes/minishell.h"

char *get_prompt(void)
{
	char *input;

	input = readline("Minishell~> ");
  // Ctrl+D
	if (!input)
	{
		write(STDOUT_FILENO, "Exit Minishell\n", 15);
		exit(0);
	}
	if (*input)
		add_history(input);
	return (input);
}
