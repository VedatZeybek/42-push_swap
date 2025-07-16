#include "push_swap.h"

t_stack	*init_stack(int *data, int size)
{
	t_stack	*stack;
	int		i;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->data = malloc(sizeof(int) * size);
	if (!stack->data)
	{
		free(stack);
		return (NULL);
	}
	i = -1;
	if (data)
	{
		while (++i < size)
			stack->data[i] = data[i];
		stack->top = size - 1;
	}
	else
		stack->top = -1;
	stack->size = size;
	return (stack);
}
