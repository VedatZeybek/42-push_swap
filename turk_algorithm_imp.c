//find min index
#include "push_swap.h"
#include <limits.h>

int	find_min_index(t_stack *a)
{
	int i;
	int	result;

	if (a->top == -1)
		return (-1);
	i = 0;
	result = 0;
	while (i < a->top)
	{
		if (a->data[result] < a->data[i])
			result = i;
		i++;
	}
	return (result);
}


//find max index

int find_max_index(t_stack *a)
{
	int	i;
	int result;

	if (a->top == -1)
		return (-1);
	i = 0;
	result = 0;
	while (i < a->top)
	{
		if (a->data[result] < a->data[i])
			result = i;
	}
	return (result);
}


//find target for value in B stack
// B boşsa en üste (index 0) yerleştir
// Value den büyük, en küçük sayının üstüne yerleştir.
//Value den büyük sayı yoksa en alta koy.

int	find_position_in_b(t_stack *b, int value)
{
	int	i;
	int	target_value;
	int target_index;

	if (b->top == -1)
		return (0);
	target_value = INT_MAX;
	i = b->top;
	target_index = -1;
	while (i > 0)
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
	else
		return (target_index);
}



//find target for value in A stack
int	find_position_in_a(t_stack *a, int value)
{
	int target_index;
	int target_value;
	int	i;

	if (a->top == -1)
		return (-1);
	i = a->top;
	target_index = 0;
	target_value = INT_MAX;
	while (i > 0)
	{
		if (a->data[i] > value && a->data[i] < target_value)
		{
			target_index = i;
			target_value = a->data[i];
		}
		i--;
	}
    if (target_index != -1) {
        return target_index;
    } else {
        return find_min_index(a);
    }
}


//rotation cost calculation
// Yukarıdan (ra/rb) kaç adım
// Aşağıdan (rra/rrb) kaç adım  

int rotation_cost(t_stack *stack, int target_index)
{
	int cost_from_up;
	int cost_from_down;

	if (target_index == stack->top || stack->top == -1)
		return (0);
	cost_from_up = stack->top - target_index;
	cost_from_down = target_index + 1;
	if (cost_from_up < cost_from_down)
		return (cost_from_up);
	else
		return (cost_from_down);
}

//push cost calculation
// Basit toplam maliyet (optimizasyon olmadan)

int	push_cost(t_stack *a, t_stack *b, int a_index)
{
	int	cost_a;
	int	cost_b;
	int	target_b;

	cost_a = rotation_cost(a, a_index);
	target_b = find_position_in_b(b, a->data[a_index]);
	if (b->top == -1)
		cost_b = 0;
	else 
		cost_b = rotation_cost(b, target_b);
	return (cost_a + cost_b);
}


// find cheapest move

int	find_cheapest_move(t_stack *a, t_stack *b)
{
	int	min_cost;
	int	cheapest_index;
	int	i;

	if (a->top == -1)
		return (-1);
	min_cost = push_cost(a, b, a->top);
	cheapest_index = a->top;
	i = a->top - 1;
	while (i > 0)
	{
		if (min_cost > push_cost(a, b, i))
		{
			min_cost =  push_cost(a, b, i);
			cheapest_index = i;
		}
		i--;
	}
	return (cheapest_index);
}



//control stack is ordered or not
// En üstten aşağı doğru küçükten büyüğe sıralı olmalı

int is_ordered(t_stack *stack)
{
	int	i;

	if (stack->top == 0 || stack->top == -1 )
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

//rotate top
void	rotate_to_top(t_stack *stack, int target_index, char stack_name)
{
	int	cost_from_up;
	int	cost_from_down;
	int	i;

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
		}
	}
	else
		while (i < cost_from_up)
		{
			if (stack_name == 'a')
				rra(stack);
			else
				rrb(stack);
		}
}


//optimal push
// B'yi doğru pozisyona getir
// A'yı doğru pozisyona getir
// Push yap

void	execute_push(t_stack *a, t_stack *b, int cheapest_index)
{
	int	target_b;

	target_b = find_target_in_b(b, a->data[cheapest_index]);
	//control eksik
	rotate_to_top(b, target_b, 'b');
	rotate_to_top(a, cheapest_index, 'a');
	pb(a, b);
}

//turk_algorithm
// Eğer zaten sıralıysa çık
// Edge case: 2 eleman varsa
// Edge case: 3 eleman varsa
// İlk iki elemanı B'ye gönder
// B'deki elemanları sırala (büyük üstte)
// A'dan B'ye optimal pushlar (3 eleman kalana kadar)
// A'daki son 3 elemanı sırala
// B'den A'ya geri al
// Son olarak minimum'u en üste getir

int	control_before_alogirthm(t_stack *a, t_stack *b)
{
	if (is_ordered(a))
		return (1);
	if (a->top == 1)
	{
		if (a->data[1] > a->data[0])
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

void	turk_algorithm(t_stack *a, t_stack *b)
{
	int	cheapest_index;

	if (control_before_alogirthm(a, b))
		return ;
	pb(a, b);
	pb(a, b);
	if (b->data[b->top] < b->data[b->top - 1])
		sb(b);
	
}