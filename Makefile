NAME = push_swap
SRC = push_swap.c turk_algorithm.c print_free_utils.c init_and_fill_stack.c \
		operation_utils1.c operation_utils2.c stack_utils.c \
		turk_algorithm_utils1.c turk_algorithm_utils2.c  \
		turk_algorithm_utils3.c turk_algorithm_utils4.c


CC = cc
CFLAGS = -Wall -Wextra -Werror


all:
	$(CC)  $(SRC) -o $(NAME)
