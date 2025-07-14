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

static void	calculate_costs(t_stack *stack, int index,
		int *up_cost, int *down_cost)
{
	if (stack->top == -1)
	{
		*up_cost = 0;
		*down_cost = 0;
	}
	*up_cost = stack->top - index;
	*down_cost = index + 1;
}

static int	get_min_cost(int a_up, int a_down, int b_up, int b_down)
{
	int	cost1;
	int	cost2;
	int	cost3;
	int	cost4;

	cost1 = ft_min(a_up, b_up) + ft_abs(a_up - b_up);
	cost2 = ft_min(a_down, b_down) + ft_abs(a_down - b_down);
	cost3 = a_up + b_down;
	cost4 = a_down + b_up;
	return (ft_min(ft_min(cost1, cost2), ft_min(cost3, cost4)));
}

int	calculate_move_cost(t_stack *a, t_stack *b, int a_index)
{
	int	target_b;
	int	a_up;
	int	a_down;
	int	b_up;
	int	b_down;

	target_b = find_position_in_b(b, a->data[a_index]);
	calculate_costs(a, a_index, &a_up, &a_down);
	calculate_costs(b, target_b, &b_up, &b_down);
	return (get_min_cost(a_up, a_down, b_up, b_down));
}
