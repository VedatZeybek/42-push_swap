#include "push_swap.h"

// void print_stacks_with_title(t_stack *a, t_stack *b, const char *title) {
//     printf("\n===========%s===========\n", title);
//     printf("stack a:\n");
//     for (int i = a->top; i >= 0; i--) {
//         printf("%d\n", a->data[i]);
//     }
//     printf("stack b:\n");
//     for (int i = b->top; i >= 0; i--) {
//         printf("%d\n", b->data[i]);
//     }
//     printf("===============================\n");
// }

int main(int argc, char **argv)
{
	int		*data_a;
	int		*data_b;
	int		*temp;
	t_stack	*stack_a;
	t_stack	*stack_b;
	
	if (argc < 2)
		return (1);
	data_a = parse_arguments(&data_a, argc, argv);
	if (data_a == NULL)
		write(2, "error\n", 6);
	data_b = NULL;
	temp = data_a;
	stack_a = init_stack(data_a, argc - 1);
	free(temp);
	stack_b = init_stack(NULL, argc - 1);
	if (is_ordered(stack_a))
		free_and_exit(stack_a, stack_b);
	turk_algorithm(stack_a, stack_b);
	free_and_exit(stack_a, stack_b);
}