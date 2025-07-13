#include "push_swap.h"

static int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a); 
}

static void calculate_costs(t_stack *stack, int index, int *up_cost, int *down_cost)
{
	if (stack->top == -1)
	{
		*up_cost = 0;
		*down_cost = 0;
	}
	*up_cost = stack->top - index;
	*down_cost = index + 1;
}

int calculate_move_cost(t_stack *a, t_stack *b, int a_index)
{
	int target_b;
	int a_up;
	int a_down;
	int b_up;
	int b_down;
	int costs[4];
	int min_cost;
	int	i;

	target_b = find_position_in_b(b, a->data[a_index]);
	calculate_costs(a, a_index, &a_up, &a_down);
	calculate_costs(b, target_b, &b_up, &b_down);
	costs[0] = ft_min(a_up, b_up) + ft_abs(a_up - b_up);			// RR + kalan
	costs[1] = ft_min(a_down, b_down) + ft_abs(a_down - b_down);    // RRR + kalan
	costs[2] = a_up + b_down;                              	 		// RA + RRB
	costs[3] = a_down + b_up;                               		// RRA + RB
	i = 0;
	min_cost = costs[0];
	while (i < 4)
		min_cost = ft_min(min_cost, costs[i++]);
	
	return min_cost;
}
