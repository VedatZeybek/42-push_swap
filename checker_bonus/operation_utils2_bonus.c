#include "push_swap_bonus.h"

void	ra_bonus(t_stack *stack_a)
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
	}
}

void	rb_bonus(t_stack *stack_b)
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
	}

}

void	rra_bonus(t_stack *stack_a)
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
	}
}

void	rrb_bonus(t_stack *stack_b)
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
	}
}

int	rotate_bonus(t_stack *stack_a, t_stack *stack_b, char *name)
{
	if (ft_strncmp(name, "rra\n", 4) == 0)
		rra_bonus(stack_a);
	else if (ft_strncmp(name, "rrb\n", 4) == 0)
		rrb_bonus(stack_b);
	else if (ft_strncmp(name, "rrr\n", 4) == 0)
	{
		rra_bonus(stack_a);
		rrb_bonus(stack_b);
	}
	else if (ft_strncmp(name, "ra\n", 3) == 0)
		ra_bonus(stack_a);
	else if (ft_strncmp(name, "rb\n", 3) == 0)
		rb_bonus(stack_b);
	else if (ft_strncmp(name, "rr\n", 3) == 0)
	{
		ra_bonus(stack_a);
		rb_bonus(stack_b);
	}
	else
		return (0);
	return (1);
}
