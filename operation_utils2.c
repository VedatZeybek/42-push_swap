#include "push_swap.h"

void	ra(t_stack *stack_a)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_a->top >= 1)
	{
		i = 0;
		temp = stack_a->data[i];
		last_value = stack_a->data[stack_a->top];
		while (i < stack_a->top)
		{
			temp2 = stack_a->data[i + 1];
			stack_a->data[i + 1] = 	temp; 
			temp = temp2;
			i++;
		}
		stack_a->data[0] = last_value;
			print_operation("ra");
	}
}

void	rb(t_stack *stack_b)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_b->top >= 1)
	{
		i = 0;
		temp = stack_b->data[i];
		last_value = stack_b->data[stack_b->top];
		while (i < stack_b->top)
		{
			temp2 = stack_b->data[i + 1];
			stack_b->data[i + 1] = 	temp; 
			temp = temp2;
			i++;
		}
		stack_b->data[0] = last_value;
		print_operation("rb");
	}

}

void	rr(t_stack *stack_a, t_stack *stack_b)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_a->top >= 1)
	{
		i = 0;
		temp = stack_a->data[i];
		last_value = stack_a->data[stack_a->top];
		while (i < stack_a->top)
		{
			temp2 = stack_a->data[i + 1];
			stack_a->data[i + 1] = 	temp; 
			temp = temp2;
			i++;
		}
		stack_a->data[0] = last_value;
		if (stack_b->top >= 1)
		{
			i = 0;
			temp = stack_b->data[i];
			last_value = stack_b->data[stack_b->top];
			while (i < stack_b->top)
			{
				temp2 = stack_b->data[i + 1];
				stack_b->data[i + 1] = 	temp; 
				temp = temp2;
				i++;
			}
			stack_b->data[0] = last_value;
			print_operation("rr");
		}
	}
}

void	rra(t_stack *stack_a)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_a->top >= 1)
	{
		i = stack_a->top;
		temp = stack_a->data[stack_a->top];
		last_value = stack_a->data[0];
		while (i > 0)
		{
			temp2 = stack_a->data[i - 1];
			stack_a->data[i - 1] = 	temp; 
			temp = temp2;
			i--;
		}
		stack_a->data[stack_a->top] = last_value;
		print_operation("rra");
	}
}

void	rrb(t_stack *stack_b)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_b->top >= 1)
	{
		i = stack_b->top;
		temp = stack_b->data[stack_b->top];
		last_value = stack_b->data[0];
		while (i > 0)
		{
			temp2 = stack_b->data[i - 1];
			stack_b->data[i - 1] = 	temp; 
			temp = temp2;
			i--;
		}
		stack_b->data[stack_b->top] = last_value;
		print_operation("rrb");	
	}
}

void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_a->top >= 1)
	{
		i = stack_a->top;
		temp = stack_a->data[stack_a->top];
		last_value = stack_a->data[0];
		while (i > 0)
		{
			temp2 = stack_a->data[i - 1];
			stack_a->data[i - 1] = 	temp; 
			temp = temp2;
			i--;
		}
		stack_a->data[stack_a->top] = last_value;
		if (stack_b->top >= 1)
		{
			i = stack_b->top;
			temp = stack_b->data[stack_b->top];
			last_value = stack_b->data[0];
			while (i > 0)
			{
				temp2 = stack_b->data[i - 1];
				stack_b->data[i - 1] = 	temp; 
				temp = temp2;
				i--;
			}
			stack_b->data[stack_b->top] = last_value;
			print_operation("rrr");
		}
	}
}
