NAME = push_swap
SRC = *.c

CC = cc
CFLAGS = -Wall -Wextra -Werror


all:
	$(CC)  $(SRC) -o $(NAME)
