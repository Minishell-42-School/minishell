/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:24 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/16 15:08:34 by ekeller-@st      ###   ########.fr       */
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
# include <errno.h> // error
# include <sys/stat.h> //stat
# include <readline/readline.h> // readline
# include <readline/history.h> // add_history
							// rl -> clear, new_line, replace, redisplay
# include <limits.h> // for long_max and min in ft_atol in exit builtin.

# define RESET  "\033[0m"
# define RED_B  "\033[1;31m"
# define GREEN  "\033[0;32m"
# define YELLOW  "\033[0;33m"

extern volatile sig_atomic_t	g_signal;

// Token Struct
typedef enum e_token_hdoc
{
	R_NO_HDOC,
	EXPAND_VAR,
	NO_EXPAND_VAR
}	t_token_hdoc;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_token_hdoc	hdoc;
	int				nbr_env_var;
	int				*expand_var;
	struct s_token	*next;
}	t_token;

// Parser Struct
typedef struct parser_state
{
	struct s_token	*current;
}	t_parser_state;

// Redirection Struct
typedef enum e_redirtype
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef enum e_hdoc
{
	NO_EXPAND,
	EXPAND,
	NO_HDOC
}	t_hdoc;

typedef struct s_redirection
{
	t_redir_type			type;
	char					*filename;
	t_hdoc					expand_hdoc;
	struct s_redirection	*next;
}	t_redirections;

typedef struct s_hdoc_env_var
{
	char	*result;
	char	*value;
	int		start;
	int		last_exit;
}	t_hdoc_env_var;

// Command Struct
typedef struct s_command
{
	char				*command_name;
	char				**args;
	int					args_count;
	t_redirections		*redirs;
	struct s_command	*next;
}	t_command;

// Environment Varible Struct
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

// MiniShell Struct
typedef struct s_shell
{
	t_token			*token_list;
	t_command		*cmd;
	t_var			*vars;
	char			**new_envp;
	char			*line;
	t_parser_state	p_state;
	int				last_status;
	char			*hdoc_file;
	int				hdoc_control;
}	t_shell;

// Functions
// init_shell.c
void			init_t_shell(t_shell *shell);
t_shell			*get_shell(void);

// main_looping.c
void			main_looping(t_shell *shell);

// prompt.c
char			*get_prompt(t_shell *shell);

// free_all.c
void			free_all(t_shell *shell, int status);

// free_loop.c
void			free_token_lst(t_token **token_lst);
void			free_loop(t_shell *shell);
void			free_vars_and_envp(t_var *vars, char **new_envp);
void			free_command_list(t_shell *shell, t_command *head);

//free_envp.c
void			free_vars_and_envp(t_var *vars, char **new_envp);
void			free_new_envp(char **new_envp);

// signal.c
void			config_signals(void);
void			heredoc_signals(void);
void			ign_signals(void);

// ----Token----
// token.c
int				get_token(t_token **token_list, char *input);

// token_utils.c
int				is_operator(char c);
int				is_wspace(char c);
void			hdoc_exp(t_token *token, char input, int control);
void			handle_control(t_token *token, int *control);

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
t_hdoc			assign_hdoc_expansion(t_token *token);
t_token			*advance_token(t_parser_state *p_state);
t_command		*init_command_struct(int *v_error);
t_redirections	*assign_redir_type(t_parser_state *p_state, \
				t_redirections *redir);

//parser.c
t_command		*parse_pipeline(int *v_error, t_parser_state *p_state);
t_command		*parse_command(int *v_error, t_parser_state *p_state);
t_redirections	*parse_redirection(int *v_error, t_parser_state *p_state);

//check_syntax.c
int				check_syntax(t_parser_state *token, int *v_error);

// parser_error.c
void			ft_error(int *v_error, char *msg);
t_redirections	*error_redir(int *v_error, char *msg);
t_command		*error_malloc(t_command	**cmd, int *v_error);
// ----Parser----

// ----Environment----
//set_env_vars.c
int				init_vars_from_envp(t_var **vars, char **envp);
int				split_env(const char *env, char **key, char **value);
int				vars_set(t_var **vars, char *key, char *value, int exported);
t_var			*var_find(t_var *vars, const char *key);
char			*var_get(t_var *vars, const char *key);

//local_vars.c
int				is_valid_identifier(char *key);
int				exec_set_local_vars(t_shell *shell);

//envp_array.c
int				var_to_envp(t_shell *s);
// ----Environment----

// ----Expansion----
//expansion.c
void			expand_all_tokens(t_shell *s);

//expansion_utils.c
int				var_name_len(char *tok_val);
int				handle_question_mark(t_shell *s, t_aux *aux, char *new);
void			handle_env_var(t_var *vars, t_aux *aux, char *new, \
				char *var_name);

//expansion_len.c
size_t			calc_new_len(t_shell *s);
// ----Expansion----

// ----Execution----
// execution.c
void			exec_cmd(t_shell *shell);

// exec_simple_cmd.c
void			exec_simple_cmd(t_shell *shell);

// get_path.c
char			*get_path(t_shell *shell, t_command *cmd);

// handle_error.c
void			handle_error(t_shell *shell, t_command *cmd);
void			print_error(char *cmd, char *msg);
void			check_error(char *path, t_command *cmd, t_shell *shell);

// - Pipe -
// exec_pipe.c
void			exec_pipe(t_shell *shell);

// exec_pipe_proc.c
void			parent_proc(t_command *cmd, int *control_fd, int fd[2]);
void			child_proc(t_shell *shell, t_command *cmd, int control_fd, \
				int fd[2]);
// -----------------

// - Redirections -
// exec_redir.c
int				definy_fd(t_command *cmd);
int				handle_out(t_redirections *redir);
int				handle_in(t_redirections *redir);
int				handle_creat(t_redirections *redir);

// heredoc.c
void			verif_heredoc(t_shell *shell, int last_exit);

// heredoc_utils.c
char			*tmpfile_name(int *heredoc_fd);
void			definy_redir(char *file_name, t_redirections *redir);
void			clean_filename(char **file_name);
void			fork_error(int heredoc_fd, char **file_name);

// loop_heredoc.c
void			loop_heredoc(t_shell *shell, t_redirections *redir, \
				int heredoc_fd, int last_exit);

// loop_heredoc_utils.c
void			str_until_now(t_hdoc_env_var *hdoc, char *line, int i);
void			join_value(t_hdoc_env_var *hdoc);
void			expand_var(t_hdoc_env_var *hdoc, char *line, int *i, \
				t_shell *shell);

// -----------------
// ----Execution----

// ----Built_ins----
// exec_builtin
int				is_builtin(t_command *cmd);
int				handle_builtin(t_shell *shell);
int				exec_builtin(t_shell *shell, t_command *cmd);
void			dup2_and_close(int std_in, int std_out);

//export_builtin.c
int				exec_export_builtin(t_shell	*s, t_command *cmd);

//export_builtin.c
int				exec_unset_builtin(t_shell *s, t_command *cmd);
int				print_sorted_export(t_var *vars);

//cd_builtin.c
int				exec_cd_builtin(t_shell *s, t_command *cmd);
//pwd_builtin.c
int				pwd_builtin(void);

//echo_builtin.c
int				exec_echo_builtin(t_command *cmd);

//env_builtin.c
int				exec_env_builtin(t_shell *s, t_command *cmd);

//exit_builtin.c
int				exec_exit_builtin(t_shell *s, t_command *cmd);

// ----Built_ins----

#endif
