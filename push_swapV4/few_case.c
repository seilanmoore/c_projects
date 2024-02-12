/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   few_case.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:59:03 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/06 15:01:46 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_stack **stack)
{
	if (!sorted(*stack))
	{
		if (get_max_pos(*stack) == 0)
			rotate_a(&(*stack), 0);
		else if (get_max_pos(*stack) == 1)
			reverse_rotate_a(&(*stack), 0);
	}
	if (!sorted(*stack))
		swap_a(&(*stack), 0);
}

void	push_min_b_few(t_stack **stack_a, t_stack **stack_b)
{
	int	i;

	i = get_min_pos(*stack_a);
	if (i == 1)
		swap_a(&(*stack_a), 0);
	else if (i > 1)
	{
		if (i <= (lst_size(*stack_a) / 2))
		{
			while (i-- > 0)
				rotate_a(&(*stack_a), 0);
		}
		else
		{
			i = lst_size(*stack_a) - i;
			while (i-- > 0)
				reverse_rotate_a(&(*stack_a), 0);
		}
	}
	if (!sorted(*stack_a))
		push_b(&(*stack_b), &(*stack_a));
}

void	sort_five(t_stack **stack_a, t_stack **stack_b)
{
	while (lst_size(*stack_a) > 3 && !(sorted(*stack_a)))
		push_min_b_few(&(*stack_a), &(*stack_b));
	sort_three(&(*stack_a));
	while (*stack_b)
		push_a(&(*stack_a), &(*stack_b));
}

void	sort_few(t_stack **stack_a, t_stack **stack_b)
{
	if (lst_size(*stack_a) == 3)
		sort_three(&(*stack_a));
	else if (lst_size(*stack_a) > 3)
		sort_five(&(*stack_a), &(*stack_b));
}
