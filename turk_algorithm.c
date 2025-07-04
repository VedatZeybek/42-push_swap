#include "push_swap_2.h"
#include <limits.h>

// Optimized minimum index finder
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

// Optimized maximum index finder
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

// Optimized position finder in B stack
int find_position_in_b(t_stack *b, int value)
{
    int i;
    int target_value;
    int target_index;

    if (b->top == -1)
        return (0);
    target_value = INT_MAX;
    i = b->top;
    target_index = -1;
    while (i >= 0)
    {
        if (b->data[i] > value && b->data[i] < target_value)
        {
            target_value = b->data[i];
            target_index = i;
        }
        i--;
    }
    if (target_index == -1)
        return (find_max_index(b));
    return (target_index);
}

// Optimized position finder in A stack
int find_position_in_a(t_stack *a, int value)
{
    int target_index;
    int target_value;
    int i;

    if (a->top == -1)
        return (-1);
    i = a->top;
    target_index = -1;
    target_value = INT_MAX;
    while (i >= 0)
    {
        if (a->data[i] > value && a->data[i] < target_value)
        {
            target_index = i;
            target_value = a->data[i];
        }
        i--;
    }
    return (target_index != -1) ? target_index : find_min_index(a);
}

// Enhanced rotation cost calculation with optimization check
int rotation_cost(t_stack *stack, int target_index)
{
    int cost_from_up;
    int cost_from_down;

    if (target_index == stack->top || stack->top == -1)
        return (0);
    cost_from_up = stack->top - target_index;
    cost_from_down = target_index + 1;
    return (cost_from_up <= cost_from_down) ? cost_from_up : cost_from_down;
}

// Enhanced push cost calculation with dual rotation optimization
int push_cost_optimized(t_stack *a, t_stack *b, int a_index)
{
    int cost_a, cost_b, target_b;
    int cost_a_up, cost_a_down, cost_b_up, cost_b_down;
    int same_direction_cost, opposite_direction_cost;

    cost_a = rotation_cost(a, a_index);
    target_b = find_position_in_b(b, a->data[a_index]);
    
    if (b->top == -1)
        return (cost_a);
    
    cost_b = rotation_cost(b, target_b);
    
    // Calculate costs for both directions
    cost_a_up = a->top - a_index;
    cost_a_down = a_index + 1;
    cost_b_up = b->top - target_b;
    cost_b_down = target_b + 1;
    
    // Check if both stacks rotate in same direction (can be optimized with rr/rrr)
    if ((cost_a_up <= cost_a_down && cost_b_up <= cost_b_down) ||
        (cost_a_up > cost_a_down && cost_b_up > cost_b_down))
    {
        same_direction_cost = (cost_a > cost_b) ? cost_a : cost_b;
        return (same_direction_cost);
    }
    
    // Different directions, no optimization possible
    return (cost_a + cost_b);
}

// Optimized cheapest move finder
int find_cheapest_move(t_stack *a, t_stack *b)
{
    int min_cost;
    int cheapest_index;
    int i;
    int current_cost;

    if (a->top == -1)
        return (-1);
    
    min_cost = push_cost_optimized(a, b, a->top);
    cheapest_index = a->top;
    i = a->top - 1;
    
    while (i >= 0)
    {
        current_cost = push_cost_optimized(a, b, i);
        if (current_cost < min_cost)
        {
            min_cost = current_cost;
            cheapest_index = i;
        }
        i--;
    }
    return (cheapest_index);
}

// Enhanced stack order checker
int is_ordered(t_stack *stack)
{
    int i;

    if (stack->top <= 0)
        return (1);
    i = stack->top;
    while (i > 0)
    {
        if (stack->data[i] > stack->data[i - 1])
            return (0);
        i--;
    }
    return (1);
}

// Optimized rotation with dual stack support
void rotate_to_top_optimized(t_stack *a, t_stack *b, int target_a, int target_b)
{
    int cost_a_up, cost_a_down, cost_b_up, cost_b_down;
    int rotate_up_a, rotate_up_b;
    int common_rotations;

    if (a->top == -1 || b->top == -1)
        return;

    cost_a_up = a->top - target_a;
    cost_a_down = target_a + 1;
    cost_b_up = b->top - target_b;
    cost_b_down = target_b + 1;

    rotate_up_a = (cost_a_up <= cost_a_down);
    rotate_up_b = (cost_b_up <= cost_b_down);

    // If both rotate in same direction, use rr/rrr
    if (rotate_up_a == rotate_up_b)
    {
        common_rotations = (rotate_up_a) ? 
            ((cost_a_up < cost_b_up) ? cost_a_up : cost_b_up) :
            ((cost_a_down < cost_b_down) ? cost_a_down : cost_b_down);
        
        // Perform common rotations
        for (int i = 0; i < common_rotations; i++)
        {
            if (rotate_up_a)
                rr(a, b);
            else
                rrr(a, b);
        }
        
        // Finish remaining rotations
        rotate_to_top(a, target_a, 'a');
        rotate_to_top(b, target_b, 'b');
    }
    else
    {
        // Different directions, rotate separately
        rotate_to_top(a, target_a, 'a');
        rotate_to_top(b, target_b, 'b');
    }
}

// Standard rotation function
void rotate_to_top(t_stack *stack, int target_index, char stack_name)
{
    int cost_from_up;
    int cost_from_down;
    int i;

    if (target_index == stack->top)
        return;
    
    i = 0;
    cost_from_up = stack->top - target_index;
    cost_from_down = target_index + 1;
    
    if (cost_from_up <= cost_from_down)
    {
        while (i < cost_from_up)
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
        while (i < cost_from_down)
        {
            if (stack_name == 'a')
                rra(stack);
            else
                rrb(stack);
            i++;
        }
    }
}

// Enhanced push execution with optimization
void execute_push_optimized(t_stack *a, t_stack *b, int cheapest_index)
{
    int target_b;
    int cost_a_up, cost_a_down, cost_b_up, cost_b_down;
    int rotate_up_a, rotate_up_b;

    target_b = find_position_in_b(b, a->data[cheapest_index]);
    
    if (b->top == -1)
    {
        rotate_to_top(a, cheapest_index, 'a');
        pb(a, b);
        return;
    }

    cost_a_up = a->top - cheapest_index;
    cost_a_down = cheapest_index + 1;
    cost_b_up = b->top - target_b;
    cost_b_down = target_b + 1;

    rotate_up_a = (cost_a_up <= cost_a_down);
    rotate_up_b = (cost_b_up <= cost_b_down);

    // Use optimized dual rotation if same direction
    if (rotate_up_a == rotate_up_b)
    {
        int common_rotations = (rotate_up_a) ? 
            ((cost_a_up < cost_b_up) ? cost_a_up : cost_b_up) :
            ((cost_a_down < cost_b_down) ? cost_a_down : cost_b_down);
        
        for (int i = 0; i < common_rotations; i++)
        {
            if (rotate_up_a)
                rr(a, b);
            else
                rrr(a, b);
        }
    }
    
    // Complete remaining rotations
    rotate_to_top(a, cheapest_index, 'a');
    rotate_to_top(b, target_b, 'b');
    pb(a, b);
}

// Check if ss (swap both) is beneficial
int should_use_ss(t_stack *a, t_stack *b)
{
    if (a->top < 1 || b->top < 1)
        return (0);
    
    // Check if swapping both stacks improves ordering
    int a_improves = (a->data[a->top] > a->data[a->top - 1]);
    int b_improves = (b->data[b->top] < b->data[b->top - 1]); // B should be desc
    
    return (a_improves && b_improves);
}

// Enhanced pre-algorithm controls with ss optimization
int control_before_algorithm(t_stack *a, t_stack *b)
{
    if (is_ordered(a))
        return (1);
    if (a->top == 1)
    {
        if (a->data[1] > a->data[0])
        {
            // Check if we can use ss instead of sa
            if (b->top >= 1 && b->data[b->top] < b->data[b->top - 1])
                ss(a, b);
            else
                sa(a);
        }
        return (1);
    }
    if (a->top == 2)
    {
        sort_threesize_stack(a);
        return (1);
    }
    return (0);
}

// Enhanced Turk Algorithm with ss optimization
void turk_algorithm_optimized(t_stack *a, t_stack *b)
{
    int cheapest_index;
    int min_index;

    if (control_before_algorithm(a, b))
        return;
    
    // Push first two elements to B
    pb(a, b);
    pb(a, b);
    
    // Sort B stack (larger on top) - check for ss opportunity
    if (b->top >= 1 && b->data[b->top] < b->data[b->top - 1])
    {
        if (should_use_ss(a, b))
            ss(a, b);
        else
            sb(b);
    }
    
    // Main algorithm loop
    while (a->top > 2)
    {
        // Check for ss opportunity before each move
        if (should_use_ss(a, b))
            ss(a, b);
        
        cheapest_index = find_cheapest_move(a, b);
        execute_push_optimized(a, b, cheapest_index);
    }
    
    // Sort remaining 3 elements in A
    sort_threesize_stack(a);
    
    // Push back from B to A
    while (b->top >= 0)
    {
        int target_a = find_position_in_a(a, b->data[b->top]);
        rotate_to_top(a, target_a, 'a');
        pa(a, b);
        
        // Check for ss opportunity after each push
        if (should_use_ss(a, b))
            ss(a, b);
    }
    
    // Final rotation to get minimum at top
    min_index = find_min_index(a);
    rotate_to_top(a, min_index, 'a');
}
