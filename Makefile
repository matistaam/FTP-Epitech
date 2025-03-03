##
## EPITECH PROJECT, 2025
## B-OOP-400-LYN-4-1-tekspice-matis.taam
## File description:
## Makefile
##

INCLUDE_DIRS	=	$(shell find include -type d)
INCLUDE_FLAGS	=	$(addprefix -I, $(INCLUDE_DIRS))

CC				=	gcc
CFLAGS			=	-W -Wall -Wextra -Werror -g3 $(INCLUDE_FLAGS)

SRC_FILES		=	$(shell find src -name "*.c")

OBJ_FILES		=	$(SRC_FILES:.c=.o)

NAME			=	myftp

RM				=	rm -f

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_FILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
