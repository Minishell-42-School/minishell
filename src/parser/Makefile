# compiler
CC = cc

# compilation flags
CFLAGS = -Wall -Werror -Wextra -g -I.

# source code
SRCS = 	main_parser.c parser_utils.c parser.c libft.c free_parser.c

# objects
OBJECTS = $(SRCS:.c=.o)

# program name
NAME = parser_minishell

# rules
all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJECTS)
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "Program cleaned."

re: fclean all
	@echo "Object files recreated."
	@echo "Program recreated."

.PHONY: all clean fclean re