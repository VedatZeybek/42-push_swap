NAME		= push_swap

BONUS_NAME	= checker

SRC 		= push_swap.c turk_algorithm.c print_free_utils.c init_and_fill_stack.c \
		operation_utils1.c operation_utils2.c stack_utils.c \
		turk_algorithm_utils1.c turk_algorithm_utils2.c  \
		turk_algorithm_utils3.c turk_algorithm_utils4.c

BONUS_SRC	= ./checker_bonus/checker_bonus.c ./checker_bonus/get_next_line_bonus.c \
		./checker_bonus/get_next_line_utils_bonus.c \
		./checker_bonus/operation_utils1_bonus.c ./checker_bonus/operation_utils2_bonus.c \
		print_free_utils.c stack_utils.c  init_and_fill_stack.c turk_algorithm_utils1.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_NAME)


all: $(NAME)


bonus: $(BONUS_NAME)


clean:
	rm -rf $(OBJ) $(BONUS_OBJ)


fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean