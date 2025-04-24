/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:24 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/17 17:54:09 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h> // printf, readline
# include <unistd.h> // write
# include <stdlib.h> // malloc, free
# include <readline/readline.h> // readline
# include <readline/history.h> // add_history
							// rl -> clear, new_line, replace, redisplay
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset

# define RESET  "\033[0m"
# define RED_B  "\033[1;31m"
# define GREEN  "\033[0;32m"
# define YELLOW  "\033[0;33m"

typedef enum e_token_type
{
	WORD,
	PIPE, // |
	REDIR_IN, // <
	REDIR_OUT, // >
	REDIR_DELIMITER, // <<
	REDIR_APPEND // >>
	// ENV_VAR // $
}	t_token_type;

typedef struct s_token
{
	t_token_type	  type;
	char			      *value;
  int             nbr_env_var;
  int             *expand_var;
	struct s_token	*next;
}	t_token;

// Functions

// prompt.c
char	*get_prompt(void);

// ->Token
// token.c
void	get_token(t_token **token_list, char *input);
// t_token_type	get_type(char *str);
int	is_operator(char c);
int	is_wspace(char c);
// create_token.c
void	create_token(t_token **token, char *t_value, t_token_type t_type, int nbr_env, int *expand);
// read_token.c
char	*read_token(char *str, int *i, int *nbr_env, int **expand);
// verif_quote.c
int verif_close_q(char *str);

// error.c
void	error_exit(char *str);

// clean_all.c
void	clean_all(t_token **token_lst);

#endif
