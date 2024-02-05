/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_mv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:16:19 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/05 18:50:46 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//ra (rotate a): Shift up all elements of stack a by 1.
//The first element becomes the last one.

void	rotate_a(t_stack **stack_a, int both_stacks)
{
	t_stack	*tmp;

	if (!(*stack_a))
		return ;
	if (!((*stack_a)->next))
		return ;
	tmp = *stack_a;
	*stack_a = (*stack_a)->next;
	tmp->next = NULL;
	lst_last(*stack_a)->next = tmp;
	if (!both_stacks)
		write(1, "ra\n", 3);
}

//rb (rotate b): Shift up all elements of stack b by 1.
//The first element becomes the last one.

void	rotate_b(t_stack **stack_b, int both_stacks)
{
	t_stack	*tmp;

	if (!(*stack_b))
		return ;
	if (!((*stack_b)->next))
		return ;
	tmp = *stack_b;
	*stack_b = (*stack_b)->next;
	tmp->next = NULL;
	lst_last(*stack_b)->next = tmp;
	if (!both_stacks)
		write(1, "rb\n", 3);
}

//rr : ra and rb at the same time.

void	rotate_a_b(t_stack **stack_a, t_stack **stack_b)
{
	if (!(*stack_a) || !(*stack_b))
		return ;
	if (!((*stack_a)->next) || !((*stack_b)->next))
		return ;
	rotate_a(&(*stack_a), 1);
	rotate_b(&(*stack_b), 1);
	write(1, "rr\n", 3);
}
