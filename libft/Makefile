NAME = libft.a

SRC = \
	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
	ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_itoa.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
	ft_printf.c printf_putchar.c printf_putstr.c printf_putnbr.c \
	printf_putnbr_unsig.c printf_puthex.c printf_putptr.c get_next_line.c \
	ft_strcmp.c ft_strndup.c ft_strcpy.c printf_stderr.c ft_printf_stderr.c

DESP = libft.h
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

# GREEN_B = \033[1;32m
# RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
# @echo "------------------------"
# @echo "|   $(GREEN_B) Libft is Ready! $(RESET)   |"
# @echo "------------------------"

%.o: %.c $(DESP)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "Libft - Clean done!"

fclean: clean
	@rm -f $(NAME)
	@echo "Libft - Full clean done!"

re: fclean all

.PHONY: all clean fclean re