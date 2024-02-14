/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:30:55 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/14 21:31:03 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

size_t	target(t_stack *stack_b, size_t index_a)
{
	t_stack	*tmp;

	tmp = stack_b;
	while (tmp->next)
	{
		if (index_a < tmp->index && index_a > tmp->next->index)
			return (tmp->next->index);
		tmp = tmp->next;
	}
	if (index_a < get_min(stack_b) || index_a > get_max(stack_b))
		return (get_max(stack_b));
	return (stack_b->index);
}

size_t	target_position(t_stack *stack_b, size_t index_a)
{
	t_stack	*tmp;

	tmp = stack_b;
	while (tmp->next)
	{
		if (index_a < tmp->index && index_a > tmp->next->index)
			return (get_node_position(stack_b, tmp->next->index));
		tmp = tmp->next;
	}
	if (index_a < get_min(stack_b) || index_a > get_max(stack_b))
		return (get_node_position(stack_b, get_max(stack_b)));
	return (0);
}

size_t	pos_to_top(t_stack *stack_b, t_stack *stack_a)
{
	size_t	size;
	size_t	index;
	size_t	index_pos;

	size = lst_size(stack_b);
	index = index_to_move(stack_a, stack_b);
	index_pos = target_position(stack_b, index);
	if (index_pos <= (size / 2))
		return (1);
	return (0);
}
