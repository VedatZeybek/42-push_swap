#include "push_swap.h"

static void get_rotation_costs(t_stack *stack, int target_index, int *cost_up, int *cost_down)
{
	*cost_up = stack->top - target_index;
	*cost_down = target_index + 1;
}

static void apply_rotations(t_stack *stack, char stack_name, int count, int up_direction)
{
	while (count-- > 0)
	{
		if (up_direction && stack_name == 'a') 
		{
			ra(stack);
			print_operation("ra");
		}
		else if (up_direction)
		{
			rb(stack);
			print_operation("rb");
		}
		else if (stack_name == 'a')
		{
			rra(stack);
			print_operation("rra");
		}
		else 
		{
			rrb(stack);
			print_operation("rrb");
		}
	}
}

void rotate_to_top(t_stack *stack, int target_index, char stack_name)
{
	int	cost_up;
	int	cost_down;
	if (target_index == stack->top || stack->top == -1 || target_index == -1)
		return ;
	get_rotation_costs(stack, target_index, &cost_up, &cost_down);
	if (cost_up <= cost_down)
	{
		apply_rotations(stack, stack_name, cost_up, 1);
	} 
	else
	{
		apply_rotations(stack, stack_name, cost_down, 0);
	}
}

void turk_algorithm(t_stack *a, t_stack *b)
{
	int cheapest_index;
	int min_index;

	if (control_before_algorithm(a, b))
		return ;
	pb(a, b);
	if (a->top > 2)
		pb(a, b);
	if (b->top > 0 && b->data[b->top] < b->data[b->top - 1])
		sb(b);
	while (a->top > 2)
	{
		cheapest_index = find_cheapest_move(a, b);
		execute_push_to_b(a, b, cheapest_index);
	}
	rotate_to_top(b, find_max_index(b), 'b');
	sort_threesize_stack(a);
	while (b->top >= 0)
	{
		int target_a = find_position_in_a(a, b->data[b->top]);
		rotate_to_top(a, target_a , 'a');
    	pa(a, b);
	}
	min_index = find_min_index(a);
	rotate_to_top(a, min_index, 'a');
}