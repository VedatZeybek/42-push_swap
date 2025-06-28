//1 typdef stack 2 init stack 3 isempty isfull 4 push_to_stack pop_from_stack 
//5 sa sb ss pa pb pp ra rb rr rra rrb rrr 6 print stack
//7 free stack and parse_arguemnts and main

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_stack 
{
	int	*data;
	int	size;
	int	top;
} t_stack;

int	is_empty(t_stack *stack)
{
	return (stack->top == -1);
}

int is_full(t_stack *stack)
{
	if (stack->top == stack->size -1)
		return (1);
	return (0);
}

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
	i = 0;
	if (data)
	{
		while (i < size)
		{
			stack->data[i] = data[i];
			i++;
		}
		stack->top = size - 1;
	}
	else
	{
		stack->top = -1;
	}
	stack->size = size;
	return(stack);
}

int	push_to_stack(t_stack *stack, int value)
{
	if (!is_full(stack))
	{
		stack->top++;
		stack->data[stack->top] = value; 
		return (1);
	}
	return (0);
}

int	pop_from_stack(t_stack *stack)
{
	int	value;

	if (!is_empty(stack))
	{
		value =  stack->data[stack->top];
		stack->data[stack->top] = 0;
		stack->top--;
		return (value);
	}
	return (0);
}

void	sa(t_stack *stack_a)
{
	int temp;
	int	top_index;

	top_index = stack_a->top;
	if (stack_a->top >= 1)
	{
		temp = stack_a->data[top_index];
		stack_a->data[top_index] = stack_a->data[top_index - 1];
		stack_a->data[top_index - 1] = temp;
	}
}

void	sb(t_stack *stack_b)
{
	int temp;
	int	top_index;

	top_index = stack_b->top;
	if (stack_b->top >= 1)
	{
		temp = stack_b->data[top_index];
		stack_b->data[top_index] = stack_b->data[top_index - 1];
		stack_b->data[top_index - 1] = temp;
	}
}

void	ss(t_stack *stack_a, t_stack *stack_b)
{
	sa(stack_a);
	sb(stack_b);
}

void	pa(t_stack *stack_a, t_stack *stack_b)
{
	int	value;

	value = pop_from_stack(stack_b);
	push_to_stack(stack_a, value);
}

void	pb(t_stack *stack_a, t_stack *stack_b)
{
	int	value;

	value = pop_from_stack(stack_a);
	push_to_stack(stack_b, value);
}

void	ra(t_stack *stack_a)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_a->top >= 2)
	{
		i = 0;
		temp = stack_a->data[i];
		last_value = stack_a->data[stack_a->top];
		while (i < stack_a->size)
		{
			temp2 = stack_a->data[i + 1];
			stack_a->data[i + 1] = 	temp; 
			temp = temp2;
			i++;
		}
		stack_a->data[0] = last_value;
	}
}

void	rb(t_stack *stack_b)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_b->top >= 2)
	{
		i = 0;
		temp = stack_b->data[i];
		last_value = stack_b->data[stack_b->top];
		while (i < stack_b->size)
		{
			temp2 = stack_b->data[i + 1];
			stack_b->data[i + 1] = 	temp; 
			temp = temp2;
			i++;
		}
		stack_b->data[0] = last_value;
	}
}

void	rr(t_stack *stack_a, t_stack *stack_b)
{
	ra(stack_a);
	rb(stack_b);
}

void	rra(t_stack *stack_a)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_a->top >= 2)
	{
		i = stack_a->top;
		temp = stack_a->data[stack_a->top];
		last_value = stack_a->data[0];
		while (i >= 0)
		{
			temp2 = stack_a->data[i - 1];
			stack_a->data[i - 1] = 	temp; 
			temp = temp2;
			i--;
		}
		stack_a->data[stack_a->top] = last_value;
	}
}

void	rrb(t_stack *stack_b)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_b->top >= 2)
	{
		i = stack_b->top;
		temp = stack_b->data[stack_b->top];
		last_value = stack_b->data[0];
		while (i >= 0)
		{
			temp2 = stack_b->data[i - 1];
			stack_b->data[i - 1] = 	temp; 
			temp = temp2;
			i--;
		}
		stack_b->data[stack_b->top] = last_value;
	}
}

void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	rra(stack_a);
	rrb(stack_b);
}


int	*parse_arguments(int **result, int argc, char **argv)
{
	int i;

	i = 0;
	*result = malloc(sizeof(int) * (argc - 1));
	if (!(*result))
		return (NULL);
	while (i < argc - 1)
	{
		(*result)[argc - 2 - i] = atoi(argv[i + 1]);
		i++;
	}
	return (*result);
}

void	sort_threesize_stack(t_stack *stack_a)
{
	int top;
	int mid;
	int bot;

	top = stack_a->data[2];
	mid = stack_a->data[1];
	bot = stack_a->data[0];
	if (stack_a->size == 2 && top > mid)
		sa(stack_a);
	if (stack_a->size != 3)
		return ;
	if (top > mid && mid > bot && top > bot) //3 2 1
	{
		sa(stack_a);
		rra(stack_a);
	}
	else if (top > mid && mid < bot && top > bot) //3 1 2
		ra(stack_a);
	else if (top > mid && mid < bot) //2 1 3
		sa(stack_a);
	else if (top < mid && mid > bot && top > bot) //2 3 1
		rra(stack_a);
	else if (top < mid && mid > bot) //1 3 2
	{
		sa(stack_a);
		ra(stack_a);
	}
}

// void	sort_algorithm(t_stack *a, t_stack *b)
// {
// 	pb(a, b);
// 	pb(a, b);

// 	if (b->data[b->top] < b->data[b->top - 1])
// 		pb(a, b);
// 	else
// 	{
// 		rb(b);
// 		pb(a, b);
// 	}

// }

void print_stack(t_stack *stack, char name)
{
	printf("stack %c:\n", name);
	for (int i = stack->top; i >= 0; i--)
		printf("%d\n", stack->data[i]);
}


int main(int argc, char **argv) {
	int		*data_a;
	int		*data_b;
	t_stack	*stack_a;
	t_stack	*stack_b;
	
	if (argc < 2) {
		printf("Insufficient Argument\n");
		return (1);
	}
	
	data_a = parse_arguments(&data_a, argc, argv);
	data_b = NULL;  // Stack B için data gerekmez
	
	stack_a = init_stack(data_a, argc - 1);  // Dolu stack
	stack_b = init_stack(NULL, argc - 1);    // Boş stack
	
	printf("==========BEFORE===========\n");
	print_stack(stack_a, 'a');
	print_stack(stack_b, 'b');
	
	printf("\n==========AFTER PB===========\n");
	pb(stack_a, stack_b);
	print_stack(stack_a, 'a');
	print_stack(stack_b, 'b');
}