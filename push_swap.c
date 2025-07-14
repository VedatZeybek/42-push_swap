#include "push_swap.h"

int	main(int argc, char **argv)
{
	int		*data_a;
	int		*temp;
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
		return (1);
	data_a = parse_arguments(&data_a, argc, argv);
	if (data_a == NULL)
		write(2, "Error\n", 6);
	temp = data_a;
	stack_a = init_stack(data_a, argc - 1);
	free(temp);
	stack_b = init_stack(NULL, argc - 1);
	if (is_ordered(stack_a))
		free_and_exit(stack_a, stack_b);
	turk_algorithm(stack_a, stack_b);
	free_and_exit(stack_a, stack_b);
}
