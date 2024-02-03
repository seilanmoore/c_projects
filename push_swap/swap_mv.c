/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_mv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:14:19 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/03 13:14:31 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//sa (swap a): Swap the first 2 elements at the top of stack a.
//Do nothing if there is only one or no elements.
void	swap_a(t_stack **stack_a, int a_b)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;

	if (*stack_a)
	{
		if ((*stack_a)->next)
		{
			first = *stack_a;
			second = (*stack_a)->next;
			third = second->next;
			first->next = third;
			second->next = first;
			*stack_a = second;
			if (!a_b)
				printf("sa\n");
		}
	}
}

//sb (swap b): Swap the first 2 elements at the top of stack b.
//Do nothing if there is only one or no elements.

void	swap_b(t_stack **stack_b, int a_b)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;

	if (*stack_b)
	{
		if ((*stack_b)->next)
		{
			first = *stack_b;
			second = (*stack_b)->next;
			third = second->next;
			first->next = third;
			second->next = first;
			*stack_b = second;
			if (!a_b)
				printf("sb\n");
		}
	}
}

//ss : sa and sb at the same time.

void	swap_a_b(t_stack **stack_a, t_stack **stack_b)
{
	if (*stack_a && *stack_b)
	{
		if ((*stack_a)->next && (*stack_b)->next)
		{
			swap_a(&(*stack_a), 1);
			swap_b(&(*stack_b), 1);
			printf("ss\n");
		}
	}
}
