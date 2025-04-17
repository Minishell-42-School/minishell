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
# define YELLOW_B  "\033[1;33m"

typedef enum e_token_type
{
	WORD,
	PIPE, // |
	REDIR_IN, // <
	REDIR_OUT, // >
	REDIR_DELIMITER, // <<
	REDIR_APPEND, // >>
	ENV_VAR // $
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

// Functions

// prompt.c
char	*get_prompt(void);

// ->Token
// create_token.c
void	create_token(t_token **token, char *t_value, t_token_type t_type);
// token.c
void	get_token(t_token **token_list, char *input);
// verif_quote.c
char	*verif_quote(char **str, int *i, int *error_code);

// error.c
void	error_exit(char *str);

// clean_all.c
void	clean_all(t_token **token_lst);

#endif
