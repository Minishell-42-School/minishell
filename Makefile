NAME = minishell

SRCDIR = src
OBJDIR = obj
INCDIR = includes
LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
RLFLAGS = -lreadline -lncurses

SRCS = main.c prompt.c clean_all.c \
			token/token.c token/create_token.c  token/get_env_var.c \
			token/read_operator.c token/read_token.c token/verif_quote.c \
			token/verif_valid_op.c

# OBJS = $(SRCS:.c=.o)
OBJS = $(SRCS:%.c=%.o)

GREEN = \033[0;32m
GREEN_B = \033[1;32m
RESET = \033[0m

all: $(OBJDIR) $(NAME)

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
# $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(GREEN)Clean done!$(RESET)"

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)Full clean done!$(RESET)"

re: fclean all

.PHONY: all clean fclean bonus re
