#include "push_swap.h"

static void	calculate_a_costs(t_stack *a, int index,
		int *cost_up, int *cost_down)
{
	*cost_up = a->top - index;
	*cost_down = index + 1;
}

static void	calculate_b_costs(t_stack *b, int target_index,
		int *cost_up, int *cost_down)
{
	if (b->top == -1)
	{
		*cost_up = 0;
		*cost_down = 0;
	}
	else
	{
		*cost_up = b->top - target_index;
		*cost_down = target_index + 1;
	}
}

static t_move	find_cheapest_tmove(int cost_a_up, int cost_a_down,
		int cost_b_up, int cost_b_down)
{
	t_move	moves[4];
	t_move	cheapest;
	int		i;

	moves[0] = (t_move){cost_a_up + cost_b_up,
		cost_a_up, cost_b_up, 0, 0};
	moves[1] = (t_move){cost_a_down + cost_b_down, 0,
		0, cost_a_down, cost_b_down};
	moves[2] = (t_move){cost_a_up + cost_b_down,
		cost_a_up, 0, 0, cost_b_down};
	moves[3] = (t_move){cost_a_down + cost_b_up, 0,
		cost_b_up, cost_a_down, 0};
	i = 0;
	cheapest = moves[0];
	while (i < 4)
	{
		if (moves[i].cost < cheapest.cost)
			cheapest = moves[i];
		i++;
	}
	return (cheapest);
}

static void	execute_moves(t_stack *a, t_stack *b, t_move *move)
{
	while (move->ra > 0 && move->rb > 0)
	{
		rotate(a, b, "rr");
		move->ra--;
		move->rb--;
	}
	while (move->rra > 0 && move->rrb > 0)
	{
		rotate(a, b, "rrr");
		move->rra--;
		move->rrb--;
	}
	while (move->ra-- > 0)
		rotate(a, b, "ra");
	while (move->rb-- > 0)
		rotate(a, b, "rb");
	while (move->rra-- > 0)
		rotate(a, b, "rra");
	while (move->rrb-- > 0)
		rotate(a, b, "rrb");
}

void	rotate_to_top_both(t_stack *a, t_stack *b,
		int cheapest_index, int target_b)
{
	int		cost_a_up;
	int		cost_a_down;
	int		cost_b_up;
	int		cost_b_down;
	t_move	best_move;

	calculate_a_costs(a, cheapest_index, &cost_a_up, &cost_a_down);
	calculate_b_costs(b, target_b, &cost_b_up, &cost_b_down);
	best_move = find_cheapest_tmove(cost_a_up, cost_a_down,
			cost_b_up, cost_b_down);
	execute_moves(a, b, &best_move);
}
