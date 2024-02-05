/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_positions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:21:50 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/05 23:51:32 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	get_node_pos(t_stack *stack, int number)
{
	size_t	pos;

	pos = 0;
	while (stack->number != number)
	{
		stack = stack->next;
		pos++;
	}
	return (pos);
}

size_t	get_index(t_stack *stack)
{
	int		min;
	t_stack	*tmp;

	tmp = stack;
	while (tmp->indexed)
		tmp = tmp->next;
	min = tmp->number;
	tmp = tmp->next;
	while (tmp)
	{
		if (min > tmp->number && !(tmp->indexed))
			min = tmp->number;
		tmp = tmp->next;
	}
	return (get_node_pos(stack, min));
}

size_t	get_min_pos(t_stack *stack)
{
	size_t	min;
	size_t	pos;
	t_stack	*tmp;

	pos = 0;
	min = stack->index;
	tmp = stack;
	stack = stack->next;
	while (stack)
	{
		if (min > stack->index)
			min = stack->index;
		stack = stack->next;
	}
	while (tmp)
	{
		if (min == tmp->index)
			return (pos);
		tmp = tmp->next;
		pos++;
	}
	return (pos);
}

size_t	get_max_pos(t_stack *stack)
{
	size_t	max;
	size_t	pos;
	t_stack	*tmp;

	pos = 0;
	max = stack->index;
	tmp = stack;
	stack = stack->next;
	while (stack)
	{
		if (max < stack->index)
			max = stack->index;
		stack = stack->next;
	}
	while (tmp)
	{
		if (max == tmp->index)
			return (pos);
		tmp = tmp->next;
		pos++;
	}
	return (pos);
}
