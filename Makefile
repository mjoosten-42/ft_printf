NAME = libftprintf.a
CC = gcc
FLAGS = -Wall -Werror -Wextra
SRC = ft_printf.c ft_printf_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	ar -crs $@ $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -c $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re
