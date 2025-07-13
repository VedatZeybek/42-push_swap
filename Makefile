NAME = push_swap
SRC = push_swap.c turk_algorithm.c helper_utils.c init_and_fill_stack.c \
		operation_utils.c operation_utils2.c stack_utils.c \
		turk_algorithm_utils1.c turk_algorithm_utils2.c 

CC = cc
CFLAGS = -Wall -Wextra -Werror


all:
	$(CC)  $(SRC) -o $(NAME)
