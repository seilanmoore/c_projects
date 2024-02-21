/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:27:52 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/21 20:57:19 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	move_both_r(t_stack **stack_a, t_stack **stack_b, size_t a, size_t b)
{
	while ((*stack_a)->index != a && (*stack_b)->index != b)
		rotate_a_b(&(*stack_a), &(*stack_b));
	while ((*stack_a)->index != a)
		rotate_a(&(*stack_a), 0);
	while ((*stack_b)->index != b)
		rotate_b(&(*stack_b), 0);
	push_a(&(*stack_a), &(*stack_b));
}

void	move_both_rr(t_stack **stack_a, t_stack **stack_b, size_t a, size_t b)
{
	while ((*stack_a)->index != a && (*stack_b)->index != b)
		reverse_rotate_a_b(&(*stack_a), &(*stack_b));
	while ((*stack_a)->index != a)
		reverse_rotate_a(&(*stack_a), 0);
	while ((*stack_b)->index != b)
		reverse_rotate_b(&(*stack_b), 0);
	push_a(&(*stack_a), &(*stack_b));
}

void	move_a(t_stack **stack_a, size_t a, size_t ptt)
{
	if (ptt)
		while ((*stack_a)->index != a)
			rotate_a(&(*stack_a), 0);
	else
		while ((*stack_a)->index != a)
			reverse_rotate_a(&(*stack_a), 0);
}

void	move_b(t_stack **stack_b, size_t b, size_t itt)
{
	if (itt)
		while ((*stack_b)->index != b)
			rotate_b(&(*stack_b), 0);
	else
		while ((*stack_b)->index != b)
			reverse_rotate_b(&(*stack_b), 0);
}

void	last_sort(t_stack **stack_a)
{
	size_t	min_a;
	size_t	half_a;

	min_a = get_min(*stack_a);
	half_a = lst_size(*stack_a) / 2;
	if (get_min_pos(*stack_a) <= half_a)
	{
		while ((*stack_a)->index != min_a)
			rotate_a(&(*stack_a), 0);
	}
	else
	{
		while ((*stack_a)->index != min_a)
			reverse_rotate_a(&(*stack_a), 0);
	}
}
