#include "push_swap_bonus.h"

int	apply_operation(t_stack *a, t_stack *b, char *str)
{
	if (ft_strncmp(str, "r", 1) == 0)
	{
		if (rotate_bonus(a, b, str) == 0)
			return (0);
	}
	else if (ft_strncmp(str, "pb\n", 3) == 0)
		pb_bonus(a, b);
	else if (ft_strncmp(str, "pa\n", 3) == 0)
		pa_bonus(a, b);
	else if (ft_strncmp(str, "sa\n", 3) == 0)
		sa_bonus(a);
	else if (ft_strncmp(str, "sb\n", 3) == 0)
		sb_bonus(b);
	else if (ft_strncmp(str, "ss\n", 3) == 0)
		ss_bonus(a, b);
	else
		return (0);
	return (1);
}

int	get_inputs(t_stack *a, t_stack *b)
{
	char	*inputs;

	inputs = get_next_line(0);
	while (inputs)
	{
		if (!apply_operation(a, b, inputs))
		{
			write(2, "Error\n", 6);
			return (0);
		}
		free(inputs);
		inputs = get_next_line(0);
	}
	return (1);
}

void	free_mallocated(t_stack *a, t_stack *b)
{
	free(a->data);
	free(b->data);
	free(a);
	free(b);
}

int	main(int argc, char **argv)
{
	int		*data;
	int		count;
	t_stack	*a;
	t_stack	*b;

	if (argc == 1)
		return (EXIT_SUCCESS);
	data = parse_arguments(argc, argv, &count);
	if (data == NULL)
	{
		free(data);
		write(2, "Error\n", 6);
		return (EXIT_FAILURE);
	}
	a = init_stack(data, count);
	free(data);
	b = init_stack(NULL, count);
	if (!get_inputs(a, b))
		return (EXIT_FAILURE);
	if (is_ordered(a) && is_empty(b))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_mallocated(a, b);
}
