/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:51:20 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/15 14:00:49 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pushable(t_stack **s_b, t_stack **s_a, size_t range, size_t limit)
{
	if ((*s_a)->index <= range)
	{
		push_b(&(*s_b), &(*s_a));
		rotate_b(&(*s_b), 0);
	}
	else if ((*s_a)->index <= limit)
		push_b(&(*s_b), &(*s_a));
	else
		rotate_a(&(*s_a), 0);
}

void	divide(t_stack **stack_a, t_stack **stack_b)
{
	size_t	limit;
	size_t	half_limit;
	size_t	old_limit;

	limit = lst_size(*stack_a) / 2;
	half_limit = limit / 2;
	while (lst_size(*stack_a) > 3)
	{
		while (get_min(*stack_a) < limit && lst_size(*stack_a) > 3)
			pushable(&(*stack_b), &(*stack_a), half_limit, limit);
		old_limit = limit;
		limit = (old_limit / 2) + old_limit;
		half_limit = (limit + old_limit) / 2;
	}
	sort_three(&(*stack_a));
}
