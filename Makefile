NAME		= push_swap

BONUS_NAME	= checker

SRC 		= push_swap.c turk_algorithm.c print_free_utils.c init_stack.c \
		operation_utils1.c operation_utils2.c stack_utils.c \
		parse_args.c turk_algorithm_utils1.c turk_algorithm_utils2.c  \
		turk_algorithm_utils3.c turk_algorithm_utils4.c

BONUS_SRC	= ./checker_bonus/checker_bonus.c ./checker_bonus/get_next_line_bonus.c \
		./checker_bonus/operation_utils1_bonus.c ./checker_bonus/operation_utils2_bonus.c \
		print_free_utils.c stack_utils.c  init_stack.c turk_algorithm_utils1.c parse_args.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT)
	@echo "Linking $(BONUS_NAME)..."
	@$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(BONUS_NAME)

$(LIBFT):
	@echo "Libft files compiling..."
	@$(MAKE) -s -C ./libft all


bonus: $(LIBFT) $(BONUS_NAME)  

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJ) $(BONUS_OBJ)
	@$(MAKE) -s -C ./libft clean

fclean: clean
	@echo "Removing binaries..."
	@rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -s -C ./libft fclean


re: fclean all

.PHONY: all bonus clean fclean re