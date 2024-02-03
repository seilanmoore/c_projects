/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_mv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:15:43 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/03 20:15:00 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//pa (push a): Take the first element at the
//top of b and put it at the top of a.
//Do nothing if b is empty.

void	push_a(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;

	if (*stack_b)
	{
		tmp = (*stack_b)->next;
		if (!(*stack_a))
		{
			(*stack_a) = (*stack_b);
			(*stack_a)->next = NULL;
			(*stack_b) = tmp;
		}
		else
		{
			(*stack_b)->next = (*stack_a);
			(*stack_a) = (*stack_b);
			(*stack_b) = tmp;
		}
		printf("pa\n");
	}
}

//pb (push b): Take the first element at the
//top of a and put it at the top of b.
//Do nothing if a is empty.

void	push_b(t_stack **stack_b, t_stack **stack_a)
{
	t_stack	*tmp;

	if (*stack_a)
	{
		tmp = (*stack_a)->next;
		if (!(*stack_b))
		{
			(*stack_b) = (*stack_a);
			(*stack_b)->next = NULL;
			(*stack_a) = tmp;
		}
		else
		{
			(*stack_a)->next = (*stack_b);
			(*stack_b) = (*stack_a);
			(*stack_a) = tmp;
		}
		printf("pb\n");
	}
}
