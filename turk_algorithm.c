#include "push_swap.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int find_min_index(t_stack *a)
{
    int i;
    int result;

    if (a->top == -1)
        return (-1);
    i = 0;
    result = 0;
    while (i <= a->top)
    {
        if (a->data[result] > a->data[i])
            result = i;
        i++;
    }
    return (result);
}

int find_max_index(t_stack *a)
{
    int i;
    int result;

    if (a->top == -1)
        return (-1);
    i = 0;
    result = 0;
    while (i <= a->top)
    {
        if (a->data[result] < a->data[i])
            result = i;
        i++;
    }
    return (result);
}

int find_position_in_b(t_stack *b, int value)
{
    int i;
	int	position;
	int temp;

    if (b->top == -1)
        return (0);
    
    i = b->top;
	position = -1;
    while (i >= 0)
    {
        if (b->data[i] < value)
        {
			temp = position;
			position = i;
			if (temp != -1 && b->data[temp] > b->data[i])
				position = temp;
		}
        i--;
    }
	if (position == -1)
		return (find_max_index(b));
	return (position);
}

int find_position_in_a(t_stack *a, int value)
{
    int i;
	int	position;
	int temp;

    if (a->top == -1)
        return (0);

    i = 0;
	position = -1;
    while (i <= a->top)
    {
		temp = position;
        if (a->data[i] > value)
		{
            position = i;
			if (temp != -1 && a->data[temp] < a->data[i])
				position = temp;
		}
        i++;
    }
	if (position == -1)
		return (find_min_index(a));
    return (position);
}

int rotation_cost(t_stack *stack, int index)
{
    int size = stack->top + 1;
    int cost_up = stack->top - index;
    int cost_down = index + 1;
    
    return (cost_up <= cost_down) ? cost_up : cost_down;
}

// int calculate_move_cost(t_stack *a, t_stack *b, int a_index)
// {
//     int cost_a, cost_b;
//     int target_b;
//     int size_a, size_b;
    
//     size_a = a->top + 1;
//     size_b = b->top + 1;
    
//     cost_a = (a->top - a_index <= a_index + 1) ? a->top - a_index : a_index + 1;
//     if (b->top == -1)
//         cost_b = 0;
//     else
//     {
//         target_b = find_position_in_b(b, a->data[a_index]);
//         cost_b = (b->top - target_b < target_b + 1) ? b->top - target_b : target_b + 1;
// 	}

//     return (cost_a + cost_b);
// }

int calculate_move_cost(t_stack *a, t_stack *b, int a_index) {
    int target_b = find_position_in_b(b, a->data[a_index]);
    int cost_a_up = a->top - a_index; // ra ile maliyet
    int cost_a_down = a_index + 1;    // rra ile maliyet
    int cost_b_up = (b->top == -1) ? 0 : b->top - target_b; // rb ile maliyet
    int cost_b_down = (b->top == -1) ? 0 : target_b + 1;    // rrb ile maliyet

    int min_cost = INT_MAX;

    // 1. ra + rb (rr ile optimize edilmiş)
    int rr_count = cost_a_up < cost_b_up ? cost_a_up : cost_b_up; // Ortak rr sayısı
    int remaining_a = cost_a_up - rr_count; // Kalan ra
    int remaining_b = cost_b_up - rr_count; // Kalan rb
    int cost_rr = rr_count + remaining_a + remaining_b;
    if (cost_rr < min_cost) min_cost = cost_rr;

    // 2. rra + rrb (rrr ile optimize edilmiş)
    int rrr_count = cost_a_down < cost_b_down ? cost_a_down : cost_b_down; // Ortak rrr sayısı
    remaining_a = cost_a_down - rrr_count; // Kalan rra
    remaining_b = cost_b_down - rrr_count; // Kalan rrb
    int cost_rrr = rrr_count + remaining_a + remaining_b;
    if (cost_rrr < min_cost) min_cost = cost_rrr;

    // 3. ra + rrb
    int cost_ra_rrb = cost_a_up + cost_b_down;
    if (cost_ra_rrb < min_cost) min_cost = cost_ra_rrb;

    // 4. rra + rb
    int cost_rra_rb = cost_a_down + cost_b_up;
    if (cost_rra_rb < min_cost) min_cost = cost_rra_rb;

    return min_cost;
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

int is_ordered(t_stack *stack)
{
    int i;

    if (stack->top <= 0)
        return (1);
    i = 0;
    while (i < stack->top)
    {
        if (stack->data[i] < stack->data[i + 1])
            return (0);
        i++;
    }
    return (1);
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

// void	rotate_to_top_both(t_stack *a, t_stack *b, int *cheapest_index, int *target_b)
// {
// 	int	above_medium_a;
// 	int	above_medium_b;
// 	int	i;
// 	int	rotation_cost_a;
// 	int rotation_cost_b;
// 	int smallest;

// 	if (a->top - *cheapest_index >= *cheapest_index + 1)
// 		above_medium_a = 1;
// 	else
// 		above_medium_a = 0;
// 	if (b->top - *target_b >= *target_b + 1)
// 		above_medium_b = 1;
// 	else
// 		above_medium_b = 0;
// 	i = 0;
// 	rotation_cost_a = rotation_cost(a, *cheapest_index);    //3
// 	rotation_cost_b = rotation_cost(b, *target_b);  	//2
// 	if (rotation_cost_b > rotation_cost_a)
// 		smallest = rotation_cost_a;
// 	else
// 		smallest = rotation_cost_b;
// 	if (above_medium_a == above_medium_b)
// 	{
// 		while (i < smallest)
// 		{
// 			if (above_medium_a)
// 			{
// 				*cheapest_index++;
// 				*target_b++;
// 				rr(a, b);
// 			}
// 			else
// 			{
// 				*cheapest_index--;
// 				*target_b--;
// 				rrr(a,b);
// 			}
// 			i++;
// 		}
// 	}
// }

void rotate_to_top_both(t_stack *a, t_stack *b, int cheapest_index, int target_b) {
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

void execute_push_to_b(t_stack *a, t_stack *b, int cheapest_index)
{
    int target_b;

    target_b = find_position_in_b(b, a->data[cheapest_index]);
	rotate_to_top_both(a, b, cheapest_index, target_b);
    pb(a, b);

}

int control_before_algorithm(t_stack *a, t_stack *b)
{
    if (is_ordered(a) || a->top == 0)
	{
        return (1);
	}
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