#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // printf, readline
#include <unistd.h> // write
# include <stdlib.h> // malloc, free
# include <readline/readline.h> // readline
# include <readline/history.h> // add_history
                              // rl -> clear, new_line, replace, redisplay
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset
// # include <limits.h> //INT_MAX

// # define RESET  "\033[0m"
// # define RED_B  "\033[1;31m"
// # define GREEN  "\033[0;32m"
// # define GREEN_B  "\033[1;32m"
// # define YELLOW  "\033[0;33m"
// # define YELLOW_B  "\033[1;33m"
// # define CYAN_B  "\033[1;36m"
// # define WHITE_B  "\033[1;37m"

// Functions
char	*get_prompt(void);

#endif
