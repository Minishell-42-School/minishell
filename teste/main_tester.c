#include "./test.h"

int main(void)
{
    printf("---------------------------\n");
    printf("|   %sMinishell Tester%s   |\n", GREEN_B, RESET);
    printf("---------------------------\n\n");

    printf("--- Compilation Test ---\n");
    check_executable();

    printf("--- Test with Simple Commands ---\n");
    exec_simple_cmd();
    printf("\n\n");

    printf("--- Test with Quotes (single and double) ---\n");
    exec_quotes();
    printf("\n");

    return (0);
}
