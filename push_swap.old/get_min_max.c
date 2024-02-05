/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_min_max.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:21:50 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/04 18:45:06 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_pos_min(t_stack *stack_a)
{
	int		pos;
	int		min;
	t_stack	*tmp;

	pos = 0;
	tmp = stack_a;
	while (tmp)
	{
		if (tmp->index == -1)
		{
			min = tmp->number;
			tmp = NULL;
		}
		else
			tmp = tmp->next;
	}
	tmp = stack_a;
	stack_a = stack_a->next;
	while (stack_a)
	{
		if (min > stack_a->number
			&& stack_a->index == -1)
			min = stack_a->number;
		stack_a = stack_a->next;
	}
	while (tmp)
	{
		if (min == tmp->number)
			return (pos);
		tmp = tmp->next;
		pos++;
	}
	return (-1);
}

int	get_pos_max(t_stack *stack_b)
{
	int		pos;
	int		max;
	t_stack	*tmp;

	pos = 0;
	max = stack_b->index;
	tmp = stack_b;
	stack_b = stack_b->next;
	while (stack_b)
	{
		if (max < stack_b->index)
			max = stack_b->index;
		stack_b = stack_b->next;
	}
	while (tmp)
	{
		if (max == tmp->index)
			return (pos);
		tmp = tmp->next;
		pos++;
	}
	return (-1);
}
