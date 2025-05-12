NAME := minishell_tester

# Dirs
TEST_DIR := .
OBJ_DIR := test_obj
PROJECT_ROOT := ..
INCLUDES := -I$(PROJECT_ROOT)/includes -I$(PROJECT_ROOT)/libft

# Libs
LIBFT := $(PROJECT_ROOT)/libft/libft.a
READLINE := -lreadline -lncurses

# Compilator
CC := cc
CFLAGS := -Wall -Wextra -Werror

# Test files
TEST_SRCS := main_tester.c check_exec_and_valg.c exec_cmd.c commands.c

TEST_OBJS := $(TEST_SRCS:%.c=%.o)

GREEN = \033[0;32m
GREEN_B = \033[1;32m
YELLOW = \033[0;33m
RESET = \033[0m

# Main rules
all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(addprefix $(OBJ_DIR)/, $(TEST_OBJS))
	@$(MAKE) -C $(PROJECT_ROOT) --no-print-directory
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBFT) $(READLINE)
	@echo "\n--- $(YELLOW)MiniShell Tester is Ready$(RESET) ---\n"

$(OBJ_DIR)/%.o: ./%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(PROJECT_ROOT) clean --no-print-directory

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(PROJECT_ROOT) fclean --no-print-directory

re: fclean all

.PHONY: all fclean clean re
