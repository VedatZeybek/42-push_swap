#include "push_swap.h"

void	sa(t_stack *stack_a)
{
	int temp;
	int	top_index;

	top_index = stack_a->top;
	if (stack_a->top >= 1)
	{
		temp = stack_a->data[top_index];
		stack_a->data[top_index] = stack_a->data[top_index - 1];
		stack_a->data[top_index - 1] = temp;
		print_operation("sa");
	}
}

void	sb(t_stack *stack_b)
{
	int temp;
	int	top_index;

	top_index = stack_b->top;
	if (stack_b->top >= 1)
	{
		temp = stack_b->data[top_index];
		stack_b->data[top_index] = stack_b->data[top_index - 1];
		stack_b->data[top_index - 1] = temp;
		print_operation("sb");

	}
}

void	ss(t_stack *stack_a, t_stack *stack_b)
{
	int temp;
	int	top_index;
	int i;
		
	top_index = stack_a->top;
	if (stack_a->top >= 1)
	{
		temp = stack_a->data[top_index];
		stack_a->data[top_index] = stack_a->data[top_index - 1];
		stack_a->data[top_index - 1] = temp;
		
		top_index = stack_b->top;
		if (stack_b->top >= 1)
		{
			temp = stack_b->data[top_index];
			stack_b->data[top_index] = stack_b->data[top_index - 1];
			stack_b->data[top_index - 1] = temp;
			print_operation("ss");
		}		
	}
}

void	pa(t_stack *stack_a, t_stack *stack_b)
{
	int	value;

	value = pop_from_stack(stack_b);
	push_to_stack(stack_a, value);
	if (value != -1)
		print_operation("pa");

}

void	pb(t_stack *stack_a, t_stack *stack_b)
{
	int	value;

	value = pop_from_stack(stack_a);
	push_to_stack(stack_b, value);
	if (value != -1)
		print_operation("pb");

}