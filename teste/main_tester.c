#include "./test.h"

int	main(void)
{
	printf("---------------------------\n");
	printf("|   %sMinishell Tester%s   |\n", GREEN_B, RESET);
	printf("---------------------------\n\n");

	printf("--- Compilation Test ---\n");
	check_executable();

	printf("--- Test with Simple Commands ---\n");
	exec_simple_cmd();
	printf("\n\n");

	printf("--- Test with a few Args ---\n");
	exec_args();
	printf("\n\n");

	printf("--- Test with Echo ---\n");
	exec_echo();
	printf("\n\n");

	// printf("--- Test with Exit ---\n");
	// exec_exit();
	// printf("\n\n");

	// printf("--- Test with differents Returns ---\n");
	// exec_returns();
	// printf("\n\n");

	// printf("--- Test with Signals ---\n");
	// exec_signals();
	// printf("\n\n");

	printf("--- Test with Quotes (single and double) ---\n");
	exec_quotes();
	printf("\n\n");

	// printf("--- Test with Environment Variable ---\n");
	// exec_env_var();
	// printf("\n\n");

	// printf("--- Test with Export ---\n");
	// exec_export();
	// printf("\n\n");

	// printf("--- Test with Unset ---\n");
	// exec_unset();
	// printf("\n\n");

	// printf("--- Test with Cd ---\n");
	// exec_cd();
	// printf("\n\n");

	// printf("--- Test with Pwd ---\n");
	// exec_pwd();
	// printf("\n\n");

	// printf("--- Test with Relative Path ---\n");
	// exec_rel_path();
	// printf("\n\n");

	// printf("--- Test with Environment Path ---\n");
	// exec_env_path();
	// printf("\n\n");

	printf("--- Test with Redirection ---\n");
	exec_redir();
	printf("\n\n");

	printf("--- Test with Pipe ---\n");
	// exec_pipe();
	printf("\n\n");

	return (0);
}
