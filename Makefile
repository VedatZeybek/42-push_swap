NAME = push_swap
SRC = push_swap.c

CC = cc
CFLAGS = -Wall -Wextra -Werror


all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
