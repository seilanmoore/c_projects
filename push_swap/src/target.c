/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:30:55 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/15 14:00:03 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

size_t	target(t_stack *stack_a, size_t index_b)
{
	t_stack	*tmp;

	tmp = stack_a;
	while (tmp->next)
	{
		if (index_b > tmp->index && index_b < tmp->next->index)
			return (tmp->next->index);
		tmp = tmp->next;
	}
	if (index_b < get_min(stack_a) || index_b > get_max(stack_a))
		return (get_min(stack_a));
	return (stack_a->index);
}

size_t	target_position(t_stack *stack_a, size_t index_b)
{
	t_stack	*tmp;

	tmp = stack_a;
	while (tmp->next)
	{
		if (index_b > tmp->index && index_b < tmp->next->index)
			return (get_node_position(stack_a, tmp->next->index));
		tmp = tmp->next;
	}
	if (index_b < get_min(stack_a) || index_b > get_max(stack_a))
		return (get_node_position(stack_a, get_min(stack_a)));
	return (0);
}

size_t	pos_to_top(t_stack *stack_a, t_stack *stack_b)
{
	size_t	size;
	size_t	index;
	size_t	index_pos;

	size = lst_size(stack_a);
	index = index_to_move(stack_b, stack_a);
	index_pos = target_position(stack_a, index);
	if (index_pos <= (size / 2))
		return (1);
	return (0);
}
