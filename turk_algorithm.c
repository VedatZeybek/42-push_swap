#include "push_swap.h"
#include <limits.h>
#include <stdio.h>

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
        if (b->data[i] > value)
        {
			temp = position;
			position = i;
			if (temp != -1 && b->data[temp] < b->data[i])
				position = temp;
		}
        i--;
    }
	if (position == -1)
		return (find_max_index(b) + 1);
	return (position);
}

int find_position_in_a(t_stack *a, int value)
{
    int i;
	int	position;

    if (a->top == -1)
        return (0);

    i = 0;
	position = -1;
    while (i <= a->top)
    {
        if (a->data[i] > value)
            position = i;
        i++;
    }
	if (position == -1)
		return (a->top + 1);
    return (position);
}

int rotation_cost(t_stack *stack, int index)
{
    int size = stack->top + 1;
    int cost_up = stack->top - index;
    int cost_down = index + 1;
    
    return (cost_up <= cost_down) ? cost_up : cost_down;
}

int calculate_move_cost(t_stack *a, t_stack *b, int a_index)
{
    int cost_a, cost_b;
    int target_b;
    int size_a, size_b;
    
    size_a = a->top + 1;
    size_b = b->top + 1;
    
    cost_a = (a->top - a_index <= a_index + 1) ? a->top - a_index : a_index + 1;
    if (b->top == -1)
        cost_b = 0;
    else
    {
        target_b = find_position_in_b(b, a->data[a_index]);
        cost_b = (b->top - target_b <= target_b + 1) ? b->top - target_b + 1 : target_b;
    }
    //printf("\ncost a: %d cost b: %d", cost_a, cost_b);
    return (cost_a + cost_b);
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
		printf("min cost: %d\n", min_cost);
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
        if (stack->data[i] > stack->data[i + 1])
            return (0);
        i++;
    }
    return (1);
}

void rotate_to_top(t_stack *stack, int target_index, char stack_name)
{
    int cost_up, cost_down;
    int i;
		printf("FLAG");

    if (target_index == stack->top || stack->top == -1 || target_index == -1)
        return ;
    
    cost_up = stack->top - target_index;
    cost_down = target_index + 1;
		printf("FLAG");
    
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

// DÜZELTME 4: Rotate to position fonksiyonu ekle

// void rotate_to_position(t_stack *stack, int target_index, char stack_name)
// {
//     int cost_up, cost_down;
//     int i;

//     if (target_index == 0 || stack->top == -1)
//         return;
    
//     cost_up = target_index;
//     cost_down = (stack->top + 1) - target_index;
    
//     if (cost_up <= cost_down)
//     {
//         i = 0;
//         while (i < cost_up)
//         {
//             if (stack_name == 'a')
//                 rra(stack);
//             else
//                 rrb(stack);
//             i++;
//         }
//     }
//     else
//     {
//         i = 0;
//         while (i < cost_down)
//         {
//             if (stack_name == 'a')
//                 ra(stack);
//             else
//                 rb(stack);
//             i++;
//         }
//     }
// }

void execute_push(t_stack *a, t_stack *b, int cheapest_index)
{
    int target_b;

    target_b = find_position_in_b(b, a->data[cheapest_index]);
    // printf("targetb: %d\n", target_b);
    // printf(": %d\n", cheapest_index);
    //if (b->top >= 0)
    //rotate_to_top(b, target_b, 'b');
	rotate_to_top(a, cheapest_index, 'a');
	
	print_stacks_with_title(a, b, "BEFORE ROTATE B:");
	printf("target b - 1: %d", target_b -1);
	printf(" b->top: %d", b->top);
	if (target_b != b->top + 1)
		rotate_to_top(b, target_b - 1, 'b');
	print_stacks_with_title(a, b, "AFTER ROTATE B:");
    pb(a, b);
	if (target_b == 0)
		rb(b);

}

// void pre_sort_small_elements(t_stack *a, t_stack *b)
// {
//     int size = a->top + 1;
//     int chunk_size;
//     int i, j;
//     int min_val, max_val;
    
//     if (size <= 3)
//         return;
    
//     min_val = a->data[0];
//     max_val = a->data[0];
//     for (i = 1; i <= a->top; i++)
//     {
//         if (a->data[i] < min_val)
//             min_val = a->data[i];
//         if (a->data[i] > max_val)
//             max_val = a->data[i];
//     }
    
//     chunk_size = (max_val - min_val) / 3;
//     int first_chunk = min_val + chunk_size;
//     int second_chunk = min_val + 2 * chunk_size;
    
//     i = a->top;
//     while (i >= 0 && a->top > 2)
//     {
//         if (a->data[i] <= first_chunk)
//         {
//             rotate_to_top(a, i, 'a');
//             pb(a, b);
//             i = a->top;
//         }
//         else
//             i--;
//     }
    
//     i = a->top;
//     while (i >= 0 && a->top > 2)
//     {
//         if (a->data[i] <= second_chunk)
//         {
//             rotate_to_top(a, i, 'a');
//             pb(a, b);
//             i = a->top;
//         }
//         else
//             i--;
//     }
// }

int control_before_algorithm(t_stack *a, t_stack *b)
{
    if (is_ordered(a) || a->top == 0)
        return (1);

    if (a->top == 1)
    {
        if (a->data[0] > a->data[1]) // DÜZELTME 5: Doğru karşılaştırma
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
        return;
    
    size = a->top + 1;
    
    // if (size > 50)
    // {
    //     pre_sort_small_elements(a, b);
    // }
    // else
    // {
    //     pb(a, b);
    //     if (a->top > 2)
    //         pb(a, b);
    // }
     pb(a, b);
        if (a->top > 2)
            pb(a, b);
    // DÜZELTME 6: Stack B'yi büyükten küçüğe sırala
    if (b->top > 0 && b->data[b->top] < b->data[b->top - 1])
        sb(b);
    
    while (a->top > 2)
    {
        cheapest_index = find_cheapest_move(a, b);
        execute_push(a, b, cheapest_index);
    }
    
    sort_threesize_stack(a);
	//print_stacks_with_title(stack_a, stack_b, "AFTER");
	print_stacks_with_title(a, b, "AFTER PUSH B:");
     

    // DÜZELTME 7: Stack B'den A'ya geri dönerken doğru pozisyonu kullan

    while (b->top >= 0)
    {
        int target_a = find_position_in_a(a, b->data[b->top]);
        rotate_to_top(a, target_a, 'a');
        pa(a, b);
    }
    
    // DÜZELTME 8: Final rotasyon - minimum elemanı en alta getir
    min_index = find_min_index(a);
    rotate_to_top(a, 0, 'a'); // Minimum elemanı en alta getir
    
    // Alternatif: Minimum elemanı en üste getir
    // rotate_to_top(a, min_index, 'a');
}