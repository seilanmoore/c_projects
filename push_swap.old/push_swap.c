/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:22:59 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/06 11:40:36 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	index_stack(t_stack **stack_a)
{
	int		i;
	int		pos;
	int		size;
	t_stack	*tmp;

	i = 0;
	tmp = (*stack_a);
	size = lst_size(*stack_a);
	while (i < size)
	{
		tmp = *stack_a;
		pos = get_pos_min(*stack_a);
		while (pos-- > 0)
			tmp = tmp->next;
		tmp->index = i;
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

void	push_min_b(t_stack	**stack_b, t_stack	**stack_a)
{
	int	range;
	int	add;
	int	pushed;
	int	limit;

	range = (lst_size(*stack_a) - 1) / 13;
	add = range + 2;
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
	t_stack	*tmp;

	if (ft_error(argc, argv))
		return (-1);
	stack_b = NULL;
	stack_a = NULL;
	i = 0;
	while (++i < argc)
	{
		tmp = new_node(atol(argv[i]));
		if (!tmp)
			return (lst_clear(&stack_a), -1);
		lst_add_back(&stack_a, tmp);
	}
	index_stack(&stack_a);
	if (sorted(stack_a))
		return (lst_clear(&stack_a), printf("Error\n"), 1);
	push_min_b(&stack_b, &stack_a);
	push_max_a(&stack_a, &stack_b);
	return (lst_clear(&stack_a), lst_clear(&stack_b), 0);
}
