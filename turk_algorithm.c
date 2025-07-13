#include "push_swap.h"

int calculate_move_cost(t_stack *a, t_stack *b, int a_index) 
{
    int target_b = find_position_in_b(b, a->data[a_index]);
    int cost_a_up = a->top - a_index;
    int cost_a_down = a_index + 1;
    int cost_b_up = (b->top == -1) ? 0 : b->top - target_b;
    int cost_b_down = (b->top == -1) ? 0 : target_b + 1;

    int min_cost = INT_MAX;
    int rr_count = cost_a_up < cost_b_up ? cost_a_up : cost_b_up;
    int remaining_a = cost_a_up - rr_count;
    int remaining_b = cost_b_up - rr_count;
    int cost_rr = rr_count + remaining_a + remaining_b;
    if (cost_rr < min_cost) min_cost = cost_rr;

    int rrr_count = cost_a_down < cost_b_down ? cost_a_down : cost_b_down;
    remaining_a = cost_a_down - rrr_count;
    remaining_b = cost_b_down - rrr_count;
    int cost_rrr = rrr_count + remaining_a + remaining_b;
    if (cost_rrr < min_cost) min_cost = cost_rrr;

    int cost_ra_rrb = cost_a_up + cost_b_down;
    if (cost_ra_rrb < min_cost) min_cost = cost_ra_rrb;

    int cost_rra_rb = cost_a_down + cost_b_up;
    if (cost_rra_rb < min_cost) min_cost = cost_rra_rb;

    return min_cost;
}


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
    int size;

    if (control_before_algorithm(a, b))
        return ;
    size = a->top + 1;
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