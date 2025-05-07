/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:24 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/05 11:11:29 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include "../libft/libft.h"
# include <stdio.h> // printf, readline

# include <unistd.h> // write, pipe, fork, dup2, execvp

# include <stdlib.h> // malloc, free, exit
# include <readline/readline.h> // readline
# include <readline/history.h> // add_history
							// rl -> clear, new_line, replace, redisplay
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset

# include <sys/types.h> // pid_t
# include <sys/wait.h> // wait

# define RESET  "\033[0m"
# define RED_B  "\033[1;31m"
# define GREEN  "\033[0;32m"
# define YELLOW  "\033[0;33m"

// Signal
extern int	g_signal;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_DELIMITER,
	REDIR_APPEND
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				nbr_env_var;
	int				*expand_var;
	struct s_token	*next;
}	t_token;

// Edu structs
typedef struct parser_state
{
	struct s_token	*current;
}	t_parser_state;

typedef enum e_redirtype
{
	R_IN,
	R_OUT,
	R_DELIMITER,
	R_APPEND
}	t_redir_type;

typedef struct redirection
{
	t_redir_type		type;
	char				*filename;
	struct redirection	*next;
}	t_redirections;

typedef struct s_command
{
	char				*command_name;
	char				**args;
	int					args_count;
	t_redirections		*redirs;
	int					nbr_env_var;
	int					*expand_var;
	struct s_command	*next;
}	t_command;

// Functions

// prompt.c
char	*get_prompt(void);

// clean_all.c
void	clean_all(t_token **token_lst);

// ----Token----
// token.c
void	get_token(t_token **token_list, char *input);
int		is_operator(char c);
int		is_wspace(char c);

// create_token.c
t_token	*init_token(void);
void	add_back(t_token **token, t_token *new);

// get_env_var.c
void	verif_env_var(char *str, t_token *token);

// read_operator.c
char	*read_operator(char *str, int *i, t_token *token);

// read_token.c
char	*read_token(char *str, int *i, t_token *token);

// verif_quote.c
int		verif_close_q(char *str);

// verif_valid_op.c
int		verif_valid_op(char *str);
// ----Token----

// signal.c
void	config_signals(void);

// ----Execution----
// get_path.c
char	*get_path(t_command *cmd);

// ----Pipe----
// pipe.c
void	exec_pipeline(t_command *cmd);

// LIB -> DELETAR
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
// ----Pipe----

// ----Execution----
#endif
