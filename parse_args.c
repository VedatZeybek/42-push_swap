#include "push_swap.h"

static int	has_duplicate(int *arr, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] == arr[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	parse_sign_and_check_empty(char *str, int *sign, int *index)
{
	*sign = 1;
	*index = 0;
	if (!str[0])
		return (0);
	if (str[0] == '-')
	{
		*sign = -1;
		(*index)++;
	}
	if (!str[*index])
		return (0);
	return (1);
}

static int	is_valid_number(char *str, long *result)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	if (!parse_sign_and_check_empty(str, &sign, &i))
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

static char	**combine_and_split(int argc, char **argv)
{
	char	*joined;
	char	*tmp;
	int		i;
	char	**result;

	joined = ft_strdup("");
	if (!joined)
		return (NULL);
	i = 1;
	while (i < argc)
	{
		tmp = ft_strjoin(joined, " ");
		free(joined);
		if (!tmp)
			return (NULL);
		joined = ft_strjoin(tmp, argv[i]);
		free(tmp);
		if (!joined)
			return (NULL);
		i++;
	}
	result = ft_split(joined, ' ');
	free(joined);
	return (result);
}

int	*parse_arguments(int argc, char **argv, int *out_size)
{
	char	**args;
	int		*numbers;
	long	num;
	int		i;
	int		count;

	args = combine_and_split(argc, argv);
	count = count_words(args);
	if (!args || count == 0)
		return (free_split(args), NULL);
	*out_size = count;
	numbers = malloc(sizeof(int) * count);
	if (!numbers)
		return (free_split(args), NULL);
	i = -1;
	while (++i < count)
	{
		if (!is_valid_number(args[i], &num))
			return (free_split(args), free(numbers), NULL);
		numbers[count - 1 - i] = (int)num;
	}
	if (has_duplicate(numbers, count))
		return (free_split(args), free(numbers), NULL);
	free_split(args);
	return (numbers);
}
