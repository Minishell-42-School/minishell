// int main(void)
// {
// 	char *input;

// 	signal(SIGINT, handle_sigint);
// 	signal(SIGQUIT, SIG_IGN);

// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break;
// 		}
// 		if (*input)
// 			add_history(input);
// 		free(input);
// 	}
// 	return (0);
// }

#include "../includes/minishell.h"

int main(void)
{
	char *line;

  while (1)
	{
		line = get_prompt();

		if (!line)
			break;

		printf("Recebido: %s\n", line);

	 	// futuro: passar linha para lexer/parser/executor
		free(line);
	}

	return 0;
}
