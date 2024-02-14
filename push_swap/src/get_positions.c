/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_positions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:21:50 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/14 21:26:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

size_t	get_min(t_stack *stack)
{
	size_t	min;

	min = stack->index;
	stack = stack->next;
	while (stack)
	{
		if (min > stack->index)
			min = stack->index;
		stack = stack->next;
	}
	return (min);
}

size_t	get_max(t_stack *stack)
{
	size_t	max;

	max = stack->index;
	stack = stack->next;
	while (stack)
	{
		if (max < stack->index)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

size_t	get_min_pos(t_stack *stack)
{
	size_t	min;
	size_t	pos;
	t_stack	*tmp;

	pos = 0;
	tmp = stack;
	min = get_min(stack);
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
