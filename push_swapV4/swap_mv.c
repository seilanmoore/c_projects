/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_mv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:14:19 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/05 18:56:43 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//sa (swap a): Swap the first 2 elements at the top of stack a.
//Do nothing if there is only one or no elements.

void	swap_a(t_stack **stack_a, int both_stacks)
{
	t_stack	*tmp;

	if (!(*stack_a))
		return ;
	if (!((*stack_a)->next))
		return ;
	tmp = *stack_a;
	*stack_a = (*stack_a)->next;
	tmp->next = (*stack_a)->next;
	(*stack_a)->next = tmp;
	if (!both_stacks)
		write(1, "sa\n", 3);
}

//sb (swap b): Swap the first 2 elements at the top of stack b.
//Do nothing if there is only one or no elements.

void	swap_b(t_stack **stack_b, int both_stacks)
{
	t_stack	*tmp;

	if (!(*stack_b))
		return ;
	if (!((*stack_b)->next))
		return ;
	tmp = *stack_b;
	*stack_b = (*stack_b)->next;
	tmp->next = (*stack_b)->next;
	(*stack_b)->next = tmp;
	if (!both_stacks)
		write(1, "sb\n", 3);
}

//ss : sa and sb at the same time.

void	swap_a_b(t_stack **stack_a, t_stack **stack_b)
{
	if (!(*stack_a) || !(*stack_b))
		return ;
	if (!((*stack_a)->next) || !((*stack_b)->next))
		return ;
	swap_a(&(*stack_a), 1);
	swap_b(&(*stack_b), 1);
	write(1, "ss\n", 3);
}
