#include "./test.h"

// --- Find executable ----
void  check_executable(void)
{
  if (access(MINISHELL_EXEC, X_OK) == 0)
    printf("Executable: ✅ OK\n\n");
  else
    printf("Executable: ❌ Not found\n\n");
}

// --- Valgrind ---
void  check_memory_leaks(const char *command)
{
  char valgrind_cmd[256];
  snprintf(valgrind_cmd, sizeof(valgrind_cmd),
           "valgrind --leak-check=full --error-exitcode=1 %s -c \"%s\" > /dev/null 2>&1",
           MINISHELL_EXEC, command);
  int ret = system(valgrind_cmd);
  if (ret == 0)
    printf("✅ Without leaks\n");
  else
    printf("❌ the program has a memory leak.\n");
}
