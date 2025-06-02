/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:24 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/02 12:30:46 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h> // printf, readline
# include <unistd.h> // write, pipe, fork, dup2, execve, close
# include <fcntl.h> // open
# include <stdlib.h> // malloc, free, exit
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset
# include <sys/types.h> // pid_t
# include <sys/wait.h> // wait
# include <readline/readline.h> // readline
# include <readline/history.h> // add_history
							// rl -> clear, new_line, replace, redisplay

# define RESET  "\033[0m"
# define RED_B  "\033[1;31m"
# define GREEN  "\033[0;32m"
# define YELLOW  "\033[0;33m"

extern volatile sig_atomic_t	g_exit_status;

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
	struct s_command	*next;
}	t_command;

typedef struct s_var
{
	char				*key;
	char				*value;
	int					exported;
	struct s_var		*next;
}	t_var;

typedef struct s_exp_aux
{
	int					i;
	int					j;
	int					k;
	int					count;
	size_t				len;
}	t_aux;

// Functions
// prompt.c
char			*get_prompt(void);

// free_all.c
void			free_token_lst(t_token **token_lst);
void			free_all(t_token **token_lst, t_command **cmd, char **new_envp);
void			free_command_list(t_command *head);
void			free_vars(t_var *vars);

//free_envp.c
void			free_new_envp(char **new_envp);

// signal.c
void			config_signals(void);
void			heredoc_signals(void);
void			ign_signals(void);

// ----Token----
// token.c
void			get_token(t_token **token_list, char *input);
int				is_operator(char c);
int				is_wspace(char c);

// create_token.c
t_token			*init_token(void);
void			add_back(t_token **token, t_token *new_t);

// get_env_var.c
void			verif_env_var(char *str, t_token *token);

// read_operator.c
char			*read_operator(char *str, int *i, t_token *token);

// read_token.c
char			*read_token(char *str, int *i, t_token *token);

// verif_quote.c
int				verif_close_q(char *str);

// verif_valid_op.c
int				verif_valid_op(char *str);

// verif_value.c
void			verif_value(t_token **token_list);
// ----Token----

// ----Parser----
//parser_utils.c
int				count_args(t_parser_state *p_state);
t_token			*advance_token(t_parser_state *p_state);
t_command		*init_command_struct(void);
t_command		*fill_cmd_args(t_parser_state *p_state, t_command *cmd);
t_redirections	*assign_redir_type(t_parser_state *p_state, \
				t_redirections *redir);

//parser.c
t_command		*parse_pipeline(t_parser_state *p_state);
t_command		*parse_command(t_parser_state *p_state);
t_command		*check_command_args(t_parser_state *p_state, t_command *cmd);
t_command		*check_redirections(t_parser_state *p_state, t_command	*cmd);
t_redirections	*parse_redirection(t_parser_state *p_state);

//check_syntax.c
int				check_syntax(t_parser_state *token);
void			ft_error(char *msg);
// ----Parser----

//set_env_vars.c
int				init_vars_from_envp(t_var **vars, char **envp);
int				split_env(const char *env, char **key, char **value);
int				vars_set(t_var **vars, char *key, char *value, int exported);
t_var			*var_find(t_var *vars, const char *key);

//expansion.c
void			expand_all_tokens(t_token *head, t_var *vars);
int				expand_one_token(t_token *tok, t_var *vars);

//expansion_utils.c
char			*var_get(t_var *vars, const char *key);
size_t			calc_new_len(t_token *tok, t_var *vars);
void			process_env_flags(t_token *tok, t_aux *aux,
					size_t *len, t_var *vars);
int				var_name_len(char *tok_val);

//envp_array.c
char			**var_to_envp(t_var *vars);

//local_vars.c
int				try_set_local_var(t_command *cmd_pipeline, t_var **vars);

// ----Execution----
// execution.c
void			exec_cmd(t_command *cmd);

// exec_simple_cmd.c
void			exec_simple_cmd(t_command *cmd);

// get_path.c
char			*get_path(t_command *cmd);

// pipe.c
void			exec_pipe(t_command *cmd);

// - Redirections -
// exec_redir.c
void			definy_fd(t_command *cmd);
void			handle_out(t_redirections *redir);
void			handle_in(t_redirections *redir);
void			handle_creat(t_redirections *redir);

// heredoc.c
void			verif_heredoc(t_command *command);

// heredoc_utils.c
char			*tmpfile_name(int *heredoc_fd);
int				loop_heredoc(t_redirections *redir, int heredoc_fd);
void			definy_redir(char *file_name, t_redirections *redir);
void			clean_filename(char **file_name);
void			fork_error(int heredoc_fd, char **file_name);
// --------

// ----Execution----

#endif
