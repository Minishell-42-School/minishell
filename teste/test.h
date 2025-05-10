#ifndef TEST_MINISHELL_H
# define TEST_MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

# define MINISHELL_EXEC "../minishell"
# define RESET  "\033[0m"
# define GREEN_B  "\033[1;32m"
# define RED_B  "\033[1;31m"
// # define YELLOW  "\033[0;33m"

// executable_and_valgrind.c
void  check_executable(void);
void  check_memory_leaks(const char *command);

// exec_cmd.c
void  exec_cmd(const char *command, char *exp_output, int *test_nbr);

// commands.c
void  exec_simple_cmd(void);
void  exec_args(void);
void  exec_echo(void);
// void  exec_exit(void);
// void  exec_returns(void);
// void  exec_signals(void);
void  exec_quotes(void);
void  exec_env_var(void);
// void  exec_export(void);
// void  exec_unset(void);
// void  exec_cd(void);
// void  exec_pwd(void);
// void  exec_rel_path(void);
// void  exec_env_path(void);
// void  exec_redir(void);
void  exec_pipe(void);

#endif
