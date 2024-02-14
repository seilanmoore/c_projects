/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_mv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:15:43 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/14 20:15:22 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

//pa (push a): Take the first element at the
//top of b and put it at the top of a.
//Do nothing if b is empty.

void	push_a(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;

	if (!(*stack_b))
		return ;
	tmp = *stack_b;
	*stack_b = (*stack_b)->next;
	tmp->next = *stack_a;
	*stack_a = tmp;
	write(1, "pa\n", 3);
}

//pb (push b): Take the first element at the
//top of a and put it at the top of b.
//Do nothing if a is empty.

void	push_b(t_stack **stack_b, t_stack **stack_a)
{
	t_stack	*tmp;

	if (!(*stack_a))
		return ;
	tmp = *stack_a;
	*stack_a = (*stack_a)->next;
	tmp->next = *stack_b;
	*stack_b = tmp;
	write(1, "pb\n", 3);
}
