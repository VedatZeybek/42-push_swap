#include "push_swap.h"

t_stack	*init_stack(int *data, int size)
{
	t_stack	*stack;
	int		i;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->data = malloc(sizeof(int) * size);
	if (!stack->data)
	{
		free(stack);
		return (NULL);
	}
	i = -1;
	if (data)
	{
		while (++i < size)
			stack->data[i] = data[i];
		stack->top = size - 1;
	}
	else
		stack->top = -1;
	stack->size = size;
	return (stack);
}

static int	parse_number(char *str, long *num, int *sign, int *start)
{
	*num = 0;
	*sign = 1;
	*start = 0;
	if (!str[0])
		return (0);
	if (str[0] == '-')
	{
		*sign = -1;
		(*start)++;
	}
	if (!str[*start])
		return (0);
	return (1);
}

static int	is_valid_number(char *str, long *result)
{
	long	num;
	int		sign;
	int		i;

	if (!parse_number(str, &num, &sign, &i))
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		num = num * 10 + (str[i++] - '0');
		if (num * sign > INT_MAX || num * sign < INT_MIN)
			return (0);
	}
	*result = num * sign;
	return (1);
}

static int	*duplicate_checker(int **data, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if ((*data)[i] == (*data)[j])
			{
				free(*data);
				*data = NULL;
				return (NULL);
			}
			j++;
		}
		i++;
	}
	return (*data);
}

int	*parse_arguments(int **result, int argc, char **argv)
{
	int		i;
	long	num;

	i = 0;
	*result = malloc(sizeof(int) * (argc - 1));
	if (!(*result))
	{
		return (NULL);
	}
	while (i < argc - 1)
	{
		if (!is_valid_number(argv[i + 1], &num))
		{
			free(*result);
			*result = NULL;
			return (NULL);
		}
		(*result)[argc - 2 - i] = (int)num;
		i++;
	}
	if (duplicate_checker(result, argc - 1) == NULL)
		return (NULL);
	return (*result);
}
