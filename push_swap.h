#ifndef PUSH_SWAP
#define PUSH_SWAP

typedef struct s_stack 
{
	int	*data;
	int	size;
	int	top;
} t_stack;

#include "stdlib.h"
#include <unistd.h>

#ifndef	INT_MAX
# define INT_MAX 2147483647
#endif

#ifndef INT_MIN
# define INT_MIN -2147483648
#endif

t_stack	*init_stack(int *data, int size);
int		is_empty(t_stack *stack);
int		is_full(t_stack *stack);
int		push_to_stack(t_stack *stack, int value);
int		pop_from_stack(t_stack *stack);
int		*parse_arguments(int **result, int argc, char **argv);
void	sa(t_stack *stack_a);
void	sb(t_stack *stack_b);
void	ss(t_stack *stack_a, t_stack *stack_b);
void	pa(t_stack *stack_a, t_stack *stack_b);
void	pb(t_stack *stack_a, t_stack *stack_b);
void	ra(t_stack *stack_a);
void	rb(t_stack *stack_b);
void	rr(t_stack *stack_a, t_stack *stack_b);
void	rra(t_stack *stack_a);
void	rrb(t_stack *stack_b);
void	rrr(t_stack *stack_a, t_stack *stack_b);
void	sort_threesize_stack(t_stack *stack_a);
void	print_operation(char *op);
void	print_error(t_stack *stack_a, t_stack *stack_b);
void	free_and_exit(t_stack *stack_a, t_stack *stack_b);
void	rotate_to_top_both(t_stack *a, t_stack *b, int cheapest_index, int target_b);

int		find_min_index(t_stack *stack);
int		find_max_index(t_stack *stack);
int		find_position_in_b(t_stack *b, int value);
int		find_position_in_a(t_stack *a, int value);
int		rotation_cost(t_stack *stack, int target_index);
int		find_cheapest_move(t_stack *a, t_stack *b);
int		is_ordered(t_stack *stack);
int		calculate_move_cost(t_stack *a, t_stack *b, int a_index);
int		control_before_algorithm(t_stack *a, t_stack *b);
void	rotate_to_top(t_stack *stack, int target_index, char stack_name);
void	execute_push_to_b(t_stack *a, t_stack *b, int cheapest_index);
void	turk_algorithm(t_stack *a, t_stack *b);


#endif