#include "./test.h"

// -- Simple Commands --
void  exec_simple_cmd(void)
{
  static int test_nbr = 1;
  // Wrong order
  // exec_cmd("/bin/ls", NULL, &test_nbr);
  exec_cmd("/bin/echo Hello", NULL, &test_nbr);
  exec_cmd("       ", "Command not found or not executable", &test_nbr);
  exec_cmd("  /bin/echo Hello  ", NULL, &test_nbr);
  exec_cmd("/bin/bla", "Command not found or not executable: No such file or directory\nError execve: No such file or directory", &test_nbr);
  // TESTS THAT I COULD'T REALIZE THE EXPECTED:
  // Empty emput - OK
  // exec_cmd("", "", &test_nbr);
  // Tab '\t' - Should retorn NULL and complete the input -OK
  // exec_cmd("				", NULL, &test_nbr);
  // Mixed tabs and white space - idem
  // exec_cmd(" 				   ", NULL, &test_nbr);
}

// -- Arguments --
void  exec_args(void)
{
  static int test_nbr = 1;
  // exec_cmd("/bin/ls", NULL, &test_nbr);
  exec_cmd("/bin/echo Hello World", NULL, &test_nbr);
}

// -- Echo --
void  exec_echo(void)
{
  static int test_nbr = 1;
  exec_cmd("echo", NULL, &test_nbr);
  exec_cmd("echo Hello World", NULL, &test_nbr);
  exec_cmd("echo Tests for 42 =D", NULL, &test_nbr);
  exec_cmd("echo Tring with q'u'o't'e's'", NULL, &test_nbr);
  // Need return the frase without \n at the end
  // exec_cmd("echo -n Hello crazy World", NULL, &test_nbr);
  // exec_cmd("echo -n Tring with q'u'o't'e's'", NULL, &test_nbr);
}

// -- Exit --
// void  exec_exit(void)
// {
//   static int test_nbr = 1;
//   exec_cmd("exit", NULL, &test_nbr);
// }

// -- Return value --
// void  exec_returns(void)
// {
  // static int test_nbr = 1;
  // exec_cmd("echo $?", NULL, &test_nbr);
  // exec_cmd("/bin/ls filethatdoesntexist", "/bin/ls: cannot access 'filethatdoesntexist': No such file or directory", &test_nbr);
  // exec_cmd("$? + $?", NULL, &test_nbr);
// }

// -- Signal --
// void  exec_signals(void)
// {
//   static int test_nbr = 1;
// }

// -- Quotes --
void  exec_quotes(void)
{
  static int test_nbr = 1;
  exec_cmd("echo Hello", NULL, &test_nbr);
  // exec_cmd("echo 'Hello Crazy World'", NULL, &test_nbr);
  exec_cmd("e'c'h''o Hello", NULL, &test_nbr);
  exec_cmd("e'c'h''o H'ell'o", NULL, &test_nbr);
  exec_cmd("e'c'h''o H\"ell\"o", "Hello", &test_nbr);
  exec_cmd("e'cho Hello", "\033[1;31mError\033[0m ~> Quote still open!", &test_nbr);
  exec_cmd("e\"cho Hello", "\033[1;31mError\033[0m ~> Quote still open!", &test_nbr);
  exec_cmd("echo Hello World", NULL, &test_nbr);
  printf("\n");
  exec_cmd("echo \"Hello World\"", "Hello World", &test_nbr);
  exec_cmd("echo \"cat lol.c | cat > lol.c\"", "cat lol.c | cat > lol.c", &test_nbr);
  exec_cmd("echo '      '", NULL, &test_nbr);
  exec_cmd("echo '|'", "|", &test_nbr);
  exec_cmd("echo '>>'", ">>", &test_nbr);
  exec_cmd("echo '$USER'", "$USER", &test_nbr);
}

// -- Environment Variables --
void  exec_env_var(void)
{
  static int test_nbr = 1;
  exec_cmd("echo $USER", NULL, &test_nbr);
  // Same as $USER
  // exec_cmd("echo \"$USER\"", NULL, &test_nbr);
  exec_cmd("echo '$USER'", "$USER", &test_nbr);
  exec_cmd("echo The '$USER' is $USER", NULL, &test_nbr);
  // All the frase inside a token with 2 vars
  // exec_cmd("echo "The \"'$USER'\" is $USER", NULL, &test_nbr);
}

// // -- Export --
// void  exec_export(void)
// {
//   static int test_nbr = 1;
// }

// // -- Unset --
// void  exec_unset(void)
// {
//   static int test_nbr = 1;
// }

// // -- Cd --
// void  exec_cd(void)
// {
//   static int test_nbr = 1;
// }

// // -- pwd --
// void  exec_pwd(void)
// {
//   static int test_nbr = 1;
// }

// // -- Relative Path --
// void  exec_rel_path(void)
// {
//   static int test_nbr = 1;
// }

// // -- Enviroment Path --
// void  exec_env_path(void)
// {
//   static int test_nbr = 1;
// }

// // -- Redirections --
// void  exec_redir(void)
// {
//   static int test_nbr = 1;
// }

// -- Pipe --
void  exec_pipe(void)
{
  static int test_nbr = 1;
  exec_cmd("ls | wc -l", NULL, &test_nbr);
  exec_cmd("ls|wc -l", NULL, &test_nbr);
  exec_cmd("/bin/ls | wc -l", NULL, &test_nbr);
  exec_cmd("echo strawberry | tr 'a-z' 'A-Z'", NULL, &test_nbr);
  exec_cmd("ls | grep .c | wc -l", NULL, &test_nbr);
  exec_cmd("cat /etc/passwd | head -n 3 | wc -l", NULL, &test_nbr);
}
