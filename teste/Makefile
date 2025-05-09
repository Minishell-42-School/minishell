NAME := test_runner

# Dirs
TEST_DIR := .
PROJECT_ROOT := ..
INCLUDES := -I$(PROJECT_ROOT)/includes -I$(PROJECT_ROOT)/libft

# Libs
LIBFT := $(PROJECT_ROOT)/libft/libft.a
READLINE := -lreadline -lncurses

# Compilator
CC := cc
CFLAGS := -Wall -Wextra -Werror

# Test files
TEST_SRCS := test_main.c
TEST_OBJS := $(TEST_SRCS:%.c=%.o)

# Main rules
all: $(NAME)

$(NAME): $(TEST_OBJS)
	@$(MAKE) -C $(PROJECT_ROOT) --no-print-directory
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBFT) $(READLINE)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TEST_OBJS)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all fclean clean re
