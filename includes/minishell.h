#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // printf, readline
#include <unistd.h> // write
# include <stdlib.h> // malloc, free
# include <readline/readline.h> // readline
# include <readline/history.h> // add_history
                              // rl -> clear, new_line, replace, redisplay
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset

// Functions
char	*get_prompt(void);

#endif
