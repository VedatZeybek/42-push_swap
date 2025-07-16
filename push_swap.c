#include "push_swap.h"

int	main(int argc, char **argv)
{
	int		*data_a;
	int		*temp;
	int		count;
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
		return (1);
	data_a = parse_arguments(argc, argv, &count);
	if (data_a == NULL)
		write(2, "Error\n", 6);
	temp = data_a;
	stack_a = init_stack(data_a, count);
	free(temp);
	stack_b = init_stack(NULL, count);
	if (is_ordered(stack_a))
		free_and_exit(stack_a, stack_b);
	turk_algorithm(stack_a, stack_b);
	free_and_exit(stack_a, stack_b);
}
