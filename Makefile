NAME = libftprintf.a
LIBFT = libft/libft.a
CC = gcc
FLAGS = -Wall -Werror -Wextra -c
SRC = ft_printf.c ft_printf_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) 
	cp $(LIBFT) .
	mv libft.a $(NAME)
	ar -crs $(NAME) $(OBJ)

$(LIBFT): 
	make -C libft

%.o: %.c
	$(CC) $(FLAGS) $^

clean:
	rm -f $(OBJ)
	make fclean -C libft

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re

test: $(NAME)
	@gcc -Wall -Werror -Wextra main.c -L. -lftprintf
	@./a.out | cat -e
	@rm a.out