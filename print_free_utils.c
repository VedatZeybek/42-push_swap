#include "push_swap.h"

void	print_operation(char *op)
{
	printf("%s\n", op);
}

void	print_error(t_stack *stack_a, t_stack *stack_b)
{
	write(2, "error\n", 6);
	free(stack_a->data);
	free(stack_b->data);
	free(stack_a);
	free(stack_b);
	exit(EXIT_FAILURE);
}

void	free_and_exit(t_stack *stack_a, t_stack *stack_b)
{
	free(stack_a->data);
	free(stack_b->data);
	free(stack_a);
	free(stack_b);
	exit(EXIT_SUCCESS);
}

