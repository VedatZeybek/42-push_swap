#include "push_swap.h"

int	is_empty(t_stack *stack)
{
	return (stack->top == -1);
}

int is_full(t_stack *stack)
{
	if (stack->top == stack->size -1)
		return (1);
	return (0);
}

int	push_to_stack(t_stack *stack, int value)
{
	if (!is_full(stack))
	{
		stack->top++;
		stack->data[stack->top] = value; 
		return (1);
	}
	return (0);
}

int	pop_from_stack(t_stack *stack)
{
	int	value;

	if (!is_empty(stack))
	{
		value =  stack->data[stack->top];
		stack->data[stack->top] = 0;
		stack->top--;
		return (value);
	}
	return (-1);
}