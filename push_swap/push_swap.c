/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:22:59 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/06 14:20:44 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_max_a(t_stack	**stack_a, t_stack **stack_b)
{
	size_t	i;

	while (*stack_b)
	{
		i = get_max_pos(*stack_b);
		if (i == 1)
			swap_b(&(*stack_b), 0);
		else if (i > 1)
		{
			if (i <= (lst_size(*stack_b) / 2))
			{
				while (i-- > 0)
					rotate_b(&(*stack_b), 0);
			}
			else
			{
				i = lst_size(*stack_b) - i;
				while (i-- > 0)
					reverse_rotate_b(&(*stack_b), 0);
			}
		}
		push_a(&(*stack_a), &(*stack_b));
	}
}

static int	pushable(t_stack **stack_b, t_stack **stack_a, size_t range)
{
	if ((*stack_a)->index <= range)
	{
		push_b(&(*stack_b), &(*stack_a));
		return (1);
	}
	rotate_a(&(*stack_a), 0);
	return (0);
}

static void	push_min_b(t_stack	**stack_b, t_stack	**stack_a)
{
	size_t	pushed;
	size_t	limit;
	size_t	range;
	size_t	add;

	pushed = 0;
	limit = lst_size(*stack_a);
	range = (lst_size(*stack_a) - 1) / 13;
	add = range + 2;
	while (lst_size(*stack_a) > 1)
	{
		while (pushed < range && pushed < limit)
		{
			if (pushable(&(*stack_b), &(*stack_a), range))
				pushed++;
		}
		if (lst_size(*stack_a) > (limit / 4))
			range += add;
		else
			range += (add / 2);
	}
	push_b(&(*stack_b), &(*stack_a));
}

int	main(int argc, char	**argv)
{
	int		i;
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (ft_error(argc, argv))
		return (-1);
	stack_a = NULL;
	stack_b = NULL;
	init_stack_a(&stack_a, argc, argv);
	if (!stack_a)
		return (write(1, "Error\n", 6), -1);
	index_stack(&stack_a);
	if (sorted(stack_a))
		return (lst_clear(&stack_a), 0);
	if (argc < 12)
		sort_few(&stack_a, &stack_b);
	else
	{
		push_min_b(&stack_b, &stack_a);
		push_max_a(&stack_a, &stack_b);
	}
	return (lst_clear(&stack_a), lst_clear(&stack_b), 0);
}
