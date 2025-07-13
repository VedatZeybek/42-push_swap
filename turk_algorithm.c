#include "push_swap.h"

void rotate_to_top_both(t_stack *a, t_stack *b, int cheapest_index, int target_b) 
{
    int cost_a_up = a->top - cheapest_index;
    int cost_a_down = cheapest_index + 1;
    int cost_b_up = (b->top == -1) ? 0 : b->top - target_b;
    int cost_b_down = (b->top == -1) ? 0 : target_b + 1;

    int ra_count = 0, rb_count = 0, rra_count = 0, rrb_count = 0;
    int min_cost = INT_MAX;

    if (cost_a_up + cost_b_up < min_cost) {
        min_cost = cost_a_up + cost_b_up;
        ra_count = cost_a_up;
        rb_count = cost_b_up;
        rra_count = 0;
        rrb_count = 0;
    }
    if (cost_a_down + cost_b_down < min_cost) {
        min_cost = cost_a_down + cost_b_down;
        ra_count = 0;
        rb_count = 0;
        rra_count = cost_a_down;
        rrb_count = cost_b_down;
    }
    if (cost_a_up + cost_b_down < min_cost) {
        min_cost = cost_a_up + cost_b_down;
        ra_count = cost_a_up;
        rb_count = 0;
        rra_count = 0;
        rrb_count = cost_b_down;
    }
    if (cost_a_down + cost_b_up < min_cost) {
        min_cost = cost_a_down + cost_b_up;
        ra_count = 0;
        rb_count = cost_b_up;
        rra_count = cost_a_down;
        rrb_count = 0;
    }
    while (ra_count > 0 && rb_count > 0) {
        rr(a, b);
        ra_count--;
        rb_count--;
    }
    while (rra_count > 0 && rrb_count > 0) {
        rrr(a, b);
        rra_count--;
        rrb_count--;
    }
    while (ra_count-- > 0) ra(a);
    while (rb_count-- > 0) rb(b);
    while (rra_count-- > 0) rra(a);
    while (rrb_count-- > 0) rrb(b);
}


void rotate_to_top(t_stack *stack, int target_index, char stack_name)
{
    int cost_up, cost_down;
    int i;

    if (target_index == stack->top || stack->top == -1 || target_index == -1)
        return ;
    
    cost_up = stack->top - target_index;
    cost_down = target_index + 1;
    
    if (cost_up <= cost_down)
    {
        i = 0;
        while (i < cost_up)
        {
            if (stack_name == 'a')
                ra(stack);
            else
                rb(stack);
            i++;
        }
    }
    else
    {
        i = 0;
        while (i < cost_down)
        {
            if (stack_name == 'a')
                rra(stack);
            else
                rrb(stack);
            i++;
        }
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