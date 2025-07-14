#include "push_swap.h"

int	find_min_index(t_stack *a)
{
	int	i;
	int	result;

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

int	find_max_index(t_stack *a)
{
	int	i;
	int	result;

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

int	find_position_in_b(t_stack *b, int value)
{
	int	i;
	int	position;
	int	temp;

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

int	find_position_in_a(t_stack *a, int value)
{
	int	i;
	int	position;
	int	temp;

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

int	is_ordered(t_stack *stack)
{
	int	i;

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
