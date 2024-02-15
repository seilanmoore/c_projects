/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:42:36 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/15 14:06:34 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

size_t	optimize_move(t_stack *s_a, t_stack *s_b, size_t a, size_t b)
{
	size_t	size_a;
	size_t	size_b;

	size_a = lst_size(s_a);
	size_b = lst_size(s_b);
	if (a <= (size_a / 2) && b <= (size_b / 2))
	{
		if (a < b)
			return (b);
		return (a);
	}
	a = size_a - a;
	b = size_b - b;
	if (a < b)
		return (b);
	return (a);
}

size_t	get_cost(t_stack *stack_b, t_stack *stack_a, size_t index_b)
{
	size_t	pos_a;
	size_t	pos_b;
	size_t	half_a;
	size_t	half_b;

	pos_a = target_position(stack_a, index_b);
	pos_b = get_node_position(stack_b, index_b);
	half_a = lst_size(stack_a) / 2;
	half_b = lst_size(stack_b) / 2;
	if (pos_a > half_a && pos_b <= half_b)
		return ((lst_size(stack_a) - pos_a) + pos_b);
	else if (pos_a <= half_a && pos_b > half_b)
		return (pos_a + (lst_size(stack_b) - pos_b));
	return (optimize_move(stack_a, stack_b, pos_a, pos_b));
}

size_t	index_to_move(t_stack *stack_b, t_stack *stack_a)
{
	t_stack	*tmp;
	size_t	cost;
	size_t	index_b;

	index_b = stack_b->index;
	tmp = stack_b->next;
	cost = get_cost(stack_b, stack_a, stack_b->index);
	while (tmp)
	{
		if (cost > get_cost(stack_b, stack_a, tmp->index))
		{
			index_b = tmp->index;
			cost = get_cost(stack_b, stack_a, tmp->index);
		}
		tmp = tmp->next;
	}
	return (index_b);
}

size_t	index_to_top(t_stack *stack_b, t_stack *stack_a)
{
	size_t	size;
	size_t	index;
	size_t	index_pos;

	size = lst_size(stack_b);
	index = index_to_move(stack_b, stack_a);
	index_pos = get_node_position(stack_b, index);
	if (index_pos <= (size / 2))
		return (1);
	return (0);
}

void	to_top(t_stack **stack_a, t_stack **stack_b)
{
	size_t	itt;
	size_t	ptt;
	size_t	index_a;
	size_t	index_b;

	itt = index_to_top(*stack_b, *stack_a);
	ptt = pos_to_top(*stack_a, *stack_b);
	index_b = index_to_move(*stack_b, *stack_a);
	index_a = target(*stack_a, index_b);
	if (itt && ptt)
		move_both_r(&(*stack_a), &(*stack_b), index_a, index_b);
	else if (!itt && !ptt)
		move_both_rr(&(*stack_a), &(*stack_b), index_a, index_b);
	else
	{
		move_a(&(*stack_a), index_a, ptt);
		move_b(&(*stack_b), index_b, itt);
		push_a(&(*stack_a), &(*stack_b));
	}
}
