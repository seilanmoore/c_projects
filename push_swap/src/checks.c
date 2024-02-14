/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:18:04 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/14 22:48:48 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

long	ft_atol(const char *str)
{
	unsigned char	*ptr;
	long			sign;
	long			nbr;

	nbr = 0;
	sign = 1;
	ptr = (unsigned char *) str;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n'
		|| *ptr == '\v' || *ptr == '\f' || *ptr == '\r')
		ptr++;
	if (*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			sign *= -1;
		ptr++;
	}
	if (*ptr == '+' || *ptr == '-')
		return (0);
	while (*ptr != '\0' && *ptr >= '0' && *ptr <= '9')
	{
		nbr = nbr * 10 + (*ptr - '0');
		ptr++;
	}
	nbr *= sign;
	return (nbr);
}

int	sorted(t_stack *stack_a)
{
	size_t	prev;

	if (!stack_a)
		return (0);
	prev = stack_a->index;
	while (stack_a->next)
	{
		if (prev > (stack_a->next)->index)
			return (0);
		stack_a = stack_a->next;
		prev = stack_a->index;
	}
	return (1);
}

int	ft_error(int argc, char **argv)
{
	int	i;
	int	j;

	i = -1;
	if (argc < 2)
		return (1);
	while (++i < argc)
		if ((ft_atol(argv[i]) == 0 && argv[i][0] != '0')
			|| ft_atol(argv[i]) < -2147483648 || ft_atol(argv[i]) > 2147483647)
			return (write(2, "Error\n", 6), 1);
	i = 0;
	while (argv[i])
	{
		j = i + 1;
		while (argv[j])
		{
			if (ft_atol(argv[i]) == ft_atol(argv[j]))
				return (write(2, "Error\n", 6), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	split_arg(t_stack **stack_a, char *argv)
{
	char	**args;
	int		argc;

	argc = 0;
	args = ft_split(argv, ' ');
	if (!args)
		return (write(2, "Error\n", 6), 0);
	while (args[argc])
		argc++;
	if (!arr_to_lst(argc, args, &(*stack_a), 1))
	{
		free_args(args);
		return (0);
	}
	free_args(args);
	return (argc);
}

int	arr_to_lst(int argc, char **argv, t_stack **stack_a, int one_arg)
{
	if (!one_arg)
		argv++;
	if (ft_error(argc, argv))
		return (0);
	init_stack_a(&(*stack_a), argc, argv);
	if (!(*stack_a))
		return (write(2, "Error\n", 6), 0);
	index_stack(&(*stack_a));
	return (argc);
}
