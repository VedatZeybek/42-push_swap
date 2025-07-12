//1 typdef stack 2 init stack 3 isempty isfull 4 push_to_stack pop_from_stack 
//5 sa sb ss pa pb pp ra rb rr rra rrb rrr 6 print stack
//7 free stack and parse_arguemnts and main

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "push_swap.h"

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

void	print_error()
{
	write(2, "error\n", 6);
	exit(EXIT_FAILURE);
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
		stack->top = -1;
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
	return (-1);
}

void print_operation(char *op)
{
	printf("%s\n", op);
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
		print_operation("sa");
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
		print_operation("sb");

	}
}

void	ss(t_stack *stack_a, t_stack *stack_b)
{
	int temp;
	int	top_index;
	int i;
		
	top_index = stack_a->top;
	if (stack_a->top >= 1)
	{
		temp = stack_a->data[top_index];
		stack_a->data[top_index] = stack_a->data[top_index - 1];
		stack_a->data[top_index - 1] = temp;
		
		top_index = stack_b->top;
		if (stack_b->top >= 1)
		{
			temp = stack_b->data[top_index];
			stack_b->data[top_index] = stack_b->data[top_index - 1];
			stack_b->data[top_index - 1] = temp;
			print_operation("ss");
		}		
	}
}

void	pa(t_stack *stack_a, t_stack *stack_b)
{
	int	value;

	value = pop_from_stack(stack_b);
	push_to_stack(stack_a, value);
	if (value != -1)
		print_operation("pa");

}

void	pb(t_stack *stack_a, t_stack *stack_b)
{
	int	value;

	value = pop_from_stack(stack_a);
	push_to_stack(stack_b, value);
	if (value != -1)
		print_operation("pb");

}

void	ra(t_stack *stack_a)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_a->top >= 1)
	{
		i = 0;
		temp = stack_a->data[i];
		last_value = stack_a->data[stack_a->top];
		while (i < stack_a->top)
		{
			temp2 = stack_a->data[i + 1];
			stack_a->data[i + 1] = 	temp; 
			temp = temp2;
			i++;
		}
		stack_a->data[0] = last_value;
			print_operation("ra");
	}
}

void	rb(t_stack *stack_b)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_b->top >= 1)
	{
		i = 0;
		temp = stack_b->data[i];
		last_value = stack_b->data[stack_b->top];
		while (i < stack_b->top)
		{
			temp2 = stack_b->data[i + 1];
			stack_b->data[i + 1] = 	temp; 
			temp = temp2;
			i++;
		}
		stack_b->data[0] = last_value;
		print_operation("rb");
	}

}

void	rr(t_stack *stack_a, t_stack *stack_b)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_a->top >= 1)
	{
		i = 0;
		temp = stack_a->data[i];
		last_value = stack_a->data[stack_a->top];
		while (i < stack_a->top)
		{
			temp2 = stack_a->data[i + 1];
			stack_a->data[i + 1] = 	temp; 
			temp = temp2;
			i++;
		}
		stack_a->data[0] = last_value;
		if (stack_b->top >= 1)
		{
			i = 0;
			temp = stack_b->data[i];
			last_value = stack_b->data[stack_b->top];
			while (i < stack_b->top)
			{
				temp2 = stack_b->data[i + 1];
				stack_b->data[i + 1] = 	temp; 
				temp = temp2;
				i++;
			}
			stack_b->data[0] = last_value;
			print_operation("rr");
		}
	}
}

void	rra(t_stack *stack_a)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_a->top >= 1)
	{
		i = stack_a->top;
		temp = stack_a->data[stack_a->top];
		last_value = stack_a->data[0];
		while (i > 0)
		{
			temp2 = stack_a->data[i - 1];
			stack_a->data[i - 1] = 	temp; 
			temp = temp2;
			i--;
		}
		stack_a->data[stack_a->top] = last_value;
		print_operation("rra");
	}
}

void	rrb(t_stack *stack_b)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_b->top >= 1)
	{
		i = stack_b->top;
		temp = stack_b->data[stack_b->top];
		last_value = stack_b->data[0];
		while (i > 0)
		{
			temp2 = stack_b->data[i - 1];
			stack_b->data[i - 1] = 	temp; 
			temp = temp2;
			i--;
		}
		stack_b->data[stack_b->top] = last_value;
		print_operation("rrb");	
	}
}

void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	int	i;
	int temp;
	int	temp2;
	int	last_value;

	if (stack_a->top >= 1)
	{
		i = stack_a->top;
		temp = stack_a->data[stack_a->top];
		last_value = stack_a->data[0];
		while (i > 0)
		{
			temp2 = stack_a->data[i - 1];
			stack_a->data[i - 1] = 	temp; 
			temp = temp2;
			i--;
		}
		stack_a->data[stack_a->top] = last_value;
		if (stack_b->top >= 1)
		{
			i = stack_b->top;
			temp = stack_b->data[stack_b->top];
			last_value = stack_b->data[0];
			while (i > 0)
			{
				temp2 = stack_b->data[i - 1];
				stack_b->data[i - 1] = 	temp; 
				temp = temp2;
				i--;
			}
			stack_b->data[stack_b->top] = last_value;
			print_operation("rrr");
		}
	}
}

static int is_valid_number(char *str, long *result)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	if (!str[0])
		return (0);
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	if (!str[i])
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

int	*duplicate_checker(int **data, int size)
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
				print_error();
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
		print_error();
		return (NULL);
	}
    while (i < argc - 1)
	{
		if (!is_valid_number(argv[i + 1], &num))
		{
			print_error();
			free(*result);
			*result = NULL;
			return NULL;
		}
		(*result)[argc - 2 - i] = (int)num;
		i++;
	}
	if (duplicate_checker(result, argc - 1) == NULL)
		return (NULL);
	return (*result);
}


void sort_threesize_stack(t_stack *stack_a)
{	
	if (stack_a->top < 1) 
		return ;
	if (stack_a->top != 2)
		return ;
	if (stack_a->top == find_max_index(stack_a))
		ra(stack_a);
	if (stack_a->top -1 == find_max_index(stack_a))
		rra(stack_a);
	if (stack_a->data[stack_a->top] > stack_a->data[stack_a->top - 1])
		sa(stack_a);
}

void print_stack(t_stack *stack, char name)
{
	printf("stack %c:\n", name);
	for (int i = stack->top; i >= 0; i--)
		printf("%d\n", stack->data[i]);
}

// Turk Algoritması Debug Versiyonu

void print_stacks_with_title(t_stack *a, t_stack *b, const char *title) {
    printf("\n===========%s===========\n", title);
    printf("stack a:\n");
    for (int i = a->top; i >= 0; i--) {
        printf("%d\n", a->data[i]);
    }
    printf("stack b:\n");
    for (int i = b->top; i >= 0; i--) {
        printf("%d\n", b->data[i]);
    }
    printf("===============================\n");
}


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
	data_b = NULL;
	temp = data_a;
	stack_a = init_stack(data_a, argc - 1);
	free(temp);
	stack_b = init_stack(NULL, argc - 1);
	//print_stacks_with_title(stack_a, stack_b, "before algorithm");
	if (is_ordered(stack_a))
		return (EXIT_SUCCESS);
	turk_algorithm(stack_a, stack_b);
	//print_stacks_with_title(stack_a, stack_b, "after algorithm");
	free(stack_a->data);
	free(stack_b->data);
	free(stack_a);
	free(stack_b);
}