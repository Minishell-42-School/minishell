#include "./test.h"

// -- Simple Commands --
void  exec_simple_cmd(void)
{
  static int test_nbr = 1;
  exec_cmd("/bin/ls", NULL, &test_nbr);
  exec_cmd("/bin/echo Hello", NULL, &test_nbr);
  exec_cmd("", "\0\n", &test_nbr);
  exec_cmd("       ", "Command not found or not executable", &test_nbr);
  // exec_cmd("				", NULL, &test_nbr); // Minishell deve retornar null e completar a palavra como o tab
  // exec_cmd(" 				   ", NULL, &test_nbr);
  exec_cmd("  /bin/echo Hello  ", NULL, &test_nbr);
}

// -- Quotes --
void  exec_quotes(void)
{
  static int test_nbr = 1;
  exec_cmd("echo Hello", NULL, &test_nbr);
  exec_cmd("e'c'h''o Hello", NULL, &test_nbr);
  exec_cmd("e'c'h''o H'ell'o", NULL, &test_nbr);
  exec_cmd("e'c'h''o H\"ell\"o", "Hello", &test_nbr);
  exec_cmd("e'cho Hello", "\033[1;31mError\033[0m ~> Quote still open!", &test_nbr);
  exec_cmd("e\"cho Hello", "\033[1;31mError\033[0m ~> Quote still open!", &test_nbr);
  exec_cmd("echo Hello Mundo", NULL, &test_nbr);
  exec_cmd("echo \"Hello Mundo\"", "Hello Mundo", &test_nbr);
}
