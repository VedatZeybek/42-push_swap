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


t_stack	*init_stack(int *data, int size)
{
	t_stack	*stack;
	int		i;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->data = malloc(sizeof(int) * size); 
	if (!data)
	{
		free(stack);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		stack->data[i] = data[i];
		i++;
	}
	stack->top = size - 1;
	stack->size = size;
	return(stack);
}

int	is_empty(t_stack *stack)
{
	if (stack->size == 0)
		return (1);
	return (0);
}

int is_full(t_stack *stack)
{
	if (stack->top == stack->size -1)
		return (1);
	return (0);
}

int	push_to_stack(t_stack *stack, int value)
{
	if (!is_full(stack))
	{
		stack->data[stack->top + 1] = value; 
		stack->top++;
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
		stack->data[stack->top] = '\0';
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
		(*result)[i] = atoi(argv[i + 1]);
		i++;
	}
	return (*result);
}

void	sort_function(t_stack stack_a, t_stack stack_b)
{
	
}

int main(int argc, char **argv)
{
	int		*data_a;
	//int		*data_b = NULL;
	t_stack	*stack_a;
	//t_stack	*stack_b;
	if (argc < 2)
	{
		printf("Unsufficient Argument\n");
		return (1);
	}
	data_a = parse_arguments(&data_a, argc, argv);
	for (int i = 0; i  < argc - 1 ; i++)
		printf("%d\n",data_a[i]);
	stack_a = init_stack(data_a, argc - 1);
	//stack_b = init_stack(data_b, argc - 1);
	printf("------------------------\n");
	int	j = 0;
	while (j < argc - 1)
	{
		printf("%d\n", stack_a->data[j]);
		j++;
	}
	//printf("stack b: %d \n", stack_b->data[0]);

}