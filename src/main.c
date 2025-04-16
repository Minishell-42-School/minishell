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
		free(line);
	}

	return 0;
}
