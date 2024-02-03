/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_min_max.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:21:50 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/03 18:17:59 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*get_min(t_stack *stack_a)
{
	t_stack	*min;
	t_stack	*tmp;

	if (!stack_a)
		return (write(1, "Error\n", 7), stack_a);
	tmp = stack_a;
	while (tmp)
	{
		if (tmp->index == -1)
			min = tmp;
		tmp = tmp->next;
	}
	while (stack_a)
	{
		if (min->number > stack_a->number && stack_a->index == -1)
			min = stack_a;
		stack_a = stack_a->next;
	}
	return (min);
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
