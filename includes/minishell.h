/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:24 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/05 10:56:09 by jcosta-b         ###   ########.fr       */
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
# include <sys/types.h> // pid_t
# include <sys/wait.h> // wait

# define RESET  "\033[0m"
# define RED_B  "\033[1;31m"
# define GREEN  "\033[0;32m"
# define YELLOW  "\033[0;33m"

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
void	add_back(t_token **token, t_token *new_t);

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

// ----Execution----
// get_path.c
char	*get_path(t_command *cmd);

// external_cmd.c
void	exec_external_cmd(t_command *cmd);
// ----Execution----

#endif
