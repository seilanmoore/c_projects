/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:18:04 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/05 22:18:03 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

	i = 0;
	if (argc < 2)
		return (1);
	if (argc < 3)
		return (write(1, "Error\n", 6), 1);
	while (++i < argc)
		if ((ft_atol(argv[i]) == 0 && argv[i][0] != '0')
			|| ft_atol(argv[i]) < -2147483648 || ft_atol(argv[i]) > 2147483647)
			return (write(1, "Error\n", 6), 1);
	i = 1;
	while (argv[i])
	{
		j = i + 1;
		while (argv[j])
		{
			if (ft_atol(argv[i]) == ft_atol(argv[j]))
				return (write(1, "Error\n", 6), 1);
			j++;
		}
		i++;
	}
	return (0);
}
