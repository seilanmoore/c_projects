/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:22:59 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/03 20:19:26 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	index_stack(t_stack **stack_a)
{
	int		i;
	t_stack	*min;

	i = 0;
	min = get_min(*stack_a);
	while (i < lst_size(*stack_a))
	{
		min->index = i;
		min = get_min(*stack_a);
		i++;
	}
}

void	push_max_a(t_stack	**stack_a, t_stack **stack_b)
{
	int	i;

	while (*stack_b)
	{
		i = get_pos_max(*stack_b);
		if (i == 1)
			swap_b(&(*stack_b));
		else if (i > 1)
		{
			if (i <= (lst_size(*stack_b) / 2))
			{
				while (i-- > 0)
					rotate_b(&(*stack_b));
			}
			else
			{
				i = lst_size(*stack_b) - i;
				while (i-- > 0)
					reverse_rotate_b(&(*stack_b));
			}
		}
		push_a(&(*stack_a), &(*stack_b));
	}
}

//13 best number for 500, 7 for 100, 6 for 50, 10 for 424, 

void	push_min_b(t_stack	**stack_b, t_stack	**stack_a)
{
	int	range;
	int	add;
	int	pushed;
	int	limit;

	range = (lst_size(*stack_a) - 1) / 15;
	add = range + 1;
	pushed = 0;
	limit = lst_size(*stack_a);
	while (lst_size(*stack_a) > 1)
	{
		while (pushed < range && pushed < limit)
		{
			if ((*stack_a)->index <= range)
			{
				push_b(&(*stack_b), &(*stack_a));
				pushed++;
			}
			else
				rotate_a(&(*stack_a));
		}
		range += add;
	}
	push_b(&(*stack_b), &(*stack_a));
}

int	main(int argc, char	**argv)
{
	int		i;
	t_stack	*stack_a;
	t_stack	*stack_b;
	t_stack	*tmp;

	if (ft_error(argc, argv))
		return (-1);
	stack_b = NULL;
	stack_a = new_node(atoi(argv[1]));
	if (!stack_a)
		return (-1);
	i = 1;
	while (++i < argc)
	{
		tmp = new_node(atoi(argv[i]));
		if (!tmp)
			return (lst_clear(&stack_a), -1);
		lst_add_back(&stack_a, tmp);
	}
	index_stack(&stack_a);
	if (sorted(stack_a))
		return (printf("Error\n"), 1);
	push_min_b(&stack_b, &stack_a);
	push_max_a(&stack_a, &stack_b);
	return (lst_clear(&stack_a), lst_clear(&stack_b), 0);
}
