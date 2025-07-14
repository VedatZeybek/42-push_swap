#include "push_swap_bonus.h"

void	sa_bonus(t_stack *stack_a)
{
	int	temp;
	int	top_index;

	top_index = stack_a->top;
	if (stack_a->top >= 1)
	{
		temp = stack_a->data[top_index];
		stack_a->data[top_index] = stack_a->data[top_index - 1];
		stack_a->data[top_index - 1] = temp;
	}
}

void	sb_bonus(t_stack *stack_b)
{
	int	temp;
	int	top_index;

	top_index = stack_b->top;
	if (stack_b->top >= 1)
	{
		temp = stack_b->data[top_index];
		stack_b->data[top_index] = stack_b->data[top_index - 1];
		stack_b->data[top_index - 1] = temp;
	}
}

void	pa_bonus(t_stack *stack_a, t_stack *stack_b)
{
	int	value;

	value = pop_from_stack(stack_b);
	push_to_stack(stack_a, value);
}

void	pb_bonus(t_stack *stack_a, t_stack *stack_b)
{
	int	value;

	value = pop_from_stack(stack_a);
	push_to_stack(stack_b, value);
}
