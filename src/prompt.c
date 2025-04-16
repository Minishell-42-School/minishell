#include "../includes/minishell.h"

char *get_prompt(void)
{
	char *input;

	input = readline("Minishell~> ");
	if (!input) // Ctrl+D
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
	if (*input)
		add_history(input);
	return (input);
}
