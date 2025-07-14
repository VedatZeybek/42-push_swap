#include "push_swap.h"

int control_before_algorithm(t_stack *a)
{
	if (is_ordered(a) || a->top == 0)
		return (1);
	if (a->top == 1)
	{
		if (a->data[0] < a->data[1])
			sa(a);
		return (1);
	}
	if (a->top == 2)
	{
		sort_threesize_stack(a);
		return (1);
	}
	return (0);
}

void sort_threesize_stack(t_stack *stack_a)
{	
	if (stack_a->top < 1) 
		return ;
	if (stack_a->top != 2)
		return ;
	if (stack_a->top == find_max_index(stack_a))
	{
		ra(stack_a);
		print_operation("ra");
	}
	if (stack_a->top -1 == find_max_index(stack_a))
	{
		rra(stack_a);
		print_operation("rra");
	}	
	if (stack_a->data[stack_a->top] > stack_a->data[stack_a->top - 1])
		sa(stack_a);
}

int find_cheapest_move(t_stack *a, t_stack *b)
{
	int min_cost;
	int cheapest_index;
	int i;
	int current_cost;

	if (a->top == -1)
		return (-1);
	min_cost = calculate_move_cost(a, b, a->top);
	cheapest_index = a->top;
	i = a->top - 1;
	while (i >= 0)
	{
		current_cost = calculate_move_cost(a, b, i);
		if (current_cost < min_cost)
		{
			min_cost = current_cost;
			cheapest_index = i;
		}
	i--;
	}
	return (cheapest_index);
}

void execute_push_to_b(t_stack *a, t_stack *b, int cheapest_index)
{
	int target_b;

	target_b = find_position_in_b(b, a->data[cheapest_index]);
	rotate_to_top_both(a, b, cheapest_index, target_b);
	pb(a, b);
}