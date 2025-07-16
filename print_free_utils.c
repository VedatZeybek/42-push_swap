#include "push_swap.h"

void	print_operation(char *op)
{
	int	i;

	i = 0;
	while (op[i])
		i++;
	write(1, op, i);
	write(1, "\n", 1);
}

void	print_error(t_stack *stack_a, t_stack *stack_b)
{
	write(2, "Error\n", 6);
	free(stack_a->data);
	free(stack_b->data);
	free(stack_a);
	free(stack_b);
	exit(EXIT_FAILURE);
}

void	free_and_exit(t_stack *stack_a, t_stack *stack_b)
{
	free(stack_a->data);
	free(stack_b->data);
	free(stack_a);
	free(stack_b);
	exit(EXIT_SUCCESS);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1unsigned;
	unsigned char	*s2unsigned;
	size_t			i;

	s1unsigned = (unsigned char *)s1;
	s2unsigned = (unsigned char *)s2;
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1unsigned[i] != s2unsigned[i])
			return (s1unsigned[i] - s2unsigned[i]);
		i++;
	}
	return (0);
}
