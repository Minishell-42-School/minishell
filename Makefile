NAME = minishell

SRCDIR = src
OBJDIR = obj
INCDIR = includes
LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RLFLAGS = -lreadline -lncurses

# NORMINETTE = norminette
# FLAGS = -R CheckForbiddenSourceHeader

VALGRIND = valgrind
SUPP = --suppressions=readline.supp
IGNRL = --leak-check=full --show-leak-kinds=all
FDS = --track-fds=yes

SRCS = main.c prompt.c init_shell.c main_looping.c free_all.c free_loop.c signal.c \
	token/token.c token/create_token.c token/get_env_var.c token/read_token.c \
	token/read_operator.c token/verif_quote.c token/verif_valid_op.c \
	token/verif_value.c \
	parser/parser_utils.c parser/parser.c parser/check_syntax.c \
	execution/execution.c execution/get_path.c execution/handle_error.c \
	execution/exec_simple_cmd.c execution/redirections/exec_redir.c \
	execution/pipe/exec_pipe.c execution/pipe/exec_pipe_proc.c \
	execution/redirections/heredoc.c execution/redirections/heredoc_utils.c \
	execution/redirections/loop_heredoc.c execution/redirections/loop_heredoc_utils.c \
	environment/set_env_vars.c expansion/expansion.c \
	expansion/expansion_len.c \
	expansion/expansion_utils.c environment/envp_array.c \
	environment/local_vars.c free_envp.c \
	builtins/export_builtin.c builtins/unset_builtin.c \
	builtins/pwd_builtin.c builtins/cd_builtin.c \
	builtins/echo_builtin.c builtins/env_builtin.c \
	builtins/exit_builtin.c builtins/export_sort.c builtins/exec_builtin.c

OBJS = $(SRCS:%.c=%.o)

GREEN = \033[0;32m
GREEN_B = \033[1;32m
RESET = \033[0m

all: $(OBJDIR) $(NAME)

# norminette:
# 	$(NORMINETTE) $(FLAGS) $(SRCS)
val:
	$(VALGRIND) ./minishell

val_sup:
	$(VALGRIND) $(IGNRL) $(SUPP) ./minishell

val_fds:
	$(VALGRIND) $(FDS) ./minishell

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(addprefix $(OBJDIR)/, $(OBJS))
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)Libft created!$(RESET)\n"
	@$(CC) $(CFLAGS) -I $(INCDIR) -o $(NAME) $(addprefix $(OBJDIR)/, $(OBJS)) $(LIBFT) $(RLFLAGS)
	@echo "-----------------------------"
	@echo "|   $(GREEN_B) MiniShell is Ready! $(RESET)   |"
	@echo "-----------------------------"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(GREEN)Clean done!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)Full clean done!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
