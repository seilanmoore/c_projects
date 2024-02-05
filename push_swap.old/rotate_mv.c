/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_mv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:16:19 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/03 20:18:16 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//ra (rotate a): Shift up all elements of stack a by 1.
//The first element becomes the last one.

void	rotate_a(t_stack **stack_a)
{
	t_stack	*first;
	t_stack	*last;

	if (*stack_a)
	{
		if ((*stack_a)->next)
		{
			first = *stack_a;
			*stack_a = first->next;
			first->next = NULL;
			last = lst_last(*stack_a);
			last->next = first;
			printf("ra\n");
		}
	}
}

//rb (rotate b): Shift up all elements of stack b by 1.
//The first element becomes the last one.

void	rotate_b(t_stack **stack_b)
{
	t_stack	*first;
	t_stack	*last;

	if (*stack_b)
	{
		if ((*stack_b)->next)
		{
			first = *stack_b;
			*stack_b = first->next;
			first->next = NULL;
			last = lst_last(*stack_b);
			last->next = first;
			printf("rb\n");
		}
	}
}

//rr : ra and rb at the same time.

void	rotate_a_(t_stack **stack_a)
{
	t_stack	*first;
	t_stack	*last;

	if (*stack_a)
	{
		if ((*stack_a)->next)
		{
			first = *stack_a;
			*stack_a = first->next;
			first->next = NULL;
			last = lst_last(*stack_a);
			last->next = first;
		}
	}
}

void	rotate_b_(t_stack **stack_b)
{
	t_stack	*first;
	t_stack	*last;

	if (*stack_b)
	{
		if ((*stack_b)->next)
		{
			first = *stack_b;
			*stack_b = first->next;
			first->next = NULL;
			last = lst_last(*stack_b);
			last->next = first;
		}
	}
}

void	rotate_a_b(t_stack **stack_a, t_stack **stack_b)
{
	if (*stack_a && *stack_b)
	{
		if ((*stack_a)->next && (*stack_b)->next)
		{
			rotate_a_(&(*stack_a));
			rotate_b_(&(*stack_b));
			printf("rr\n");
		}
	}
}
