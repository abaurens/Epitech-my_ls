##
## Makefile for ls in /home/baurens/Work/Tek1/Projects/PSU/PSU_2016_my_ls/
##
## Made by Arthur Baurens
## Login   <arthur.baurens@epitech.eu>
##
## Started on  Sun Dec  4 20:52:57 2016 Arthur Baurens
## Last update Sun Dec  4 23:05:32 2016 Arthur Baurens
##

CC		=	gcc

NAME	=	my_ls

SRC		=	main.c			\
			list.c			\
			errors.c		\
			display.c		\
			string.c		\
			sorting.c		\
			parsing.c		\
			display_dir.c	\
			display_file.c

OBJ		=	$(SRC:.c=.o)

INCLUDE	=	-I./include

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

CFLAGS	+=	$(INCLUDE) -W -Wall -Wextra -pedantic

all:	$(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
