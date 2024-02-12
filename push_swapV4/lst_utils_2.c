/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:22:27 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/06 20:19:05 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*get_node(t_stack *stack, size_t position)
{
	while (position > 0)
	{
		stack = (stack)->next;
		position--;
	}
	return (stack);
}

size_t	get_node_position(t_stack *stack, size_t index)
{
	size_t	position;

	position = 0;
	while (stack)
	{
		if (stack->index == index)
			return (position);
		stack = stack->next;
		position++;
	}
	return (position);
}
