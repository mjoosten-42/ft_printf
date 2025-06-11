NAME = libft_printf.a

CC = gcc

HFLAGS  = -MMD -MP
CFLAGS  = -Wall -Wextra -Werror
LDFLAGS = 

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib

LIBFT = lib/libft/libft.a

export MAKEFLAGS = "-j 8"

include make/sources.mk
include make/headers.mk
include make/include.mk

INCLUDES += -I lib/libft/include

OBJECTS = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES:.c=.o))

DEBUG   ?= 1
VERBOSE ?= 0

ifeq ($(DEBUG), 1)
	CFLAGS += -O0 -g3
endif

ifeq ($(VERBOSE), 1)
	CFLAGS += -DVERBOSE
endif

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -crs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(HFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) -r $(OBJ_DIR)
	make -C lib/libft clean

fclean: clean
	$(RM) $(NAME)
	make -C lib/libft fclean

$(LIBFT):
	make -C lib/libft

re:
	make fclean
	make all

test:
	$(CC) -g main.c $(NAME) lib/libft/libft.a && ./a.out

ppe:
	$(CC) $(CFLAGS) $(INCLUDES) -E src/integer.c | clang-format

files:
	./make/make_sources.sh

print: 
	@echo "---SOURCES: $(SOURCES)" | xargs -n1
	@echo "---HEADERS: $(HEADERS)" | xargs -n1
	@echo "---OBJECTS: $(OBJECTS)" | xargs -n1

format: files
	clang-format -i $(SOURCES) $(HEADERS)

scan: clean
	scan-build make

ctags:
	ctags $(SOURCES) $(HEADERS)

.PHONY: all test clean fclean re files print format scan ctags

-include $(OBJECTS:.o=.d)

