NAME = push_swap
SRC = push_swap.c  turk_algorithm.c

CC = cc
CFLAGS = -Wall -Wextra -Werror


all:
	$(CC)  $(SRC) -o $(NAME)
