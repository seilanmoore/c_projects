/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate_mv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:17:07 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/14 20:15:28 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

//rra (reverse rotate a): Shift down all elements of stack a by 1.
//The last element becomes the first one.

void	reverse_rotate_a(t_stack **stack_a, int both_stacks)
{
	t_stack	*tmp;
	t_stack	*first;

	if (!(*stack_a))
		return ;
	if (!((*stack_a)->next))
		return ;
	first = *stack_a;
	tmp = *stack_a;
	*stack_a = lst_last(*stack_a);
	while ((tmp->next)->next)
	{
		if ((tmp->next)->next == *stack_a)
			(tmp->next)->next = NULL;
		else
			tmp = tmp->next;
	}
	if (*stack_a == first->next)
		first->next = NULL;
	(*stack_a)->next = first;
	if (!both_stacks)
		write(1, "rra\n", 4);
}

//rrb (reverse rotate b): Shift down all elements of stack b by 1.
//The last element becomes the first one.

void	reverse_rotate_b(t_stack **stack_b, int both_stacks)
{
	t_stack	*tmp;
	t_stack	*first;

	if (!(*stack_b))
		return ;
	if (!((*stack_b)->next))
		return ;
	first = *stack_b;
	tmp = *stack_b;
	*stack_b = lst_last(*stack_b);
	while ((tmp->next)->next)
	{
		if ((tmp->next)->next == *stack_b)
			(tmp->next)->next = NULL;
		else
			tmp = tmp->next;
	}
	if (*stack_b == first->next)
		first->next = NULL;
	(*stack_b)->next = first;
	if (!both_stacks)
		write(1, "rrb\n", 4);
}

//rrr : rra and rrb at the same time.

void	reverse_rotate_a_b(t_stack **stack_a, t_stack **stack_b)
{
	if (!(*stack_a) || !(*stack_b))
		return ;
	if (!((*stack_a)->next) || !((*stack_b)->next))
		return ;
	reverse_rotate_a(&(*stack_a), 1);
	reverse_rotate_b(&(*stack_b), 1);
	write(1, "rrr\n", 4);
}
