/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:50:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/07 14:48:19 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	get_median(t_stack *stack)
{
	size_t	sum;
	size_t	size;

	if (!stack)
		return (0);
	sum = 0;
	size = lst_size(stack);
	while (stack)
	{
		sum += stack->index;
		stack = stack->next;
	}
	return (sum / size);
}

int	pushable(t_stack **stack_b, t_stack **stack_a, size_t range)
{
	if ((*stack_a)->index <= range)
	{
		push_b(&(*stack_b), &(*stack_a));
		return (1);
	}
	rotate_a(&(*stack_a), 0);
	return (0);
}

void	divide(t_stack **stack_a, t_stack **stack_b)
{
	size_t	limit;
	size_t	half_limit;

	while (lst_size(*stack_a) > 3)
	{
		limit = get_median(*stack_a);
		half_limit = (limit + get_min(*stack_a)) / 2;
		while (get_min(*stack_a) <= half_limit && lst_size(*stack_a) > 3)
			pushable(&(*stack_b), &(*stack_a), half_limit);
		while (get_min(*stack_a) < limit && lst_size(*stack_a) > 3)
			pushable(&(*stack_b), &(*stack_a), limit);
	}
	sort_three(&(*stack_a));
}

size_t	get_pos_target(t_stack *stack_a, size_t index)
{
	t_stack		*tmp;
	size_t		target;
	size_t		lst_value;

	tmp = stack_a;
	target = 0;
	while (tmp->next)
	{
		if (index > tmp->index && index < tmp->next->index)
			return (tmp->next->index);
		tmp = tmp->next;
	}
	return (get_max(stack_a));
}

size_t	cost_a(t_stack *stack_a, size_t index, size_t steps, int move, size_t *index_a)
{
	size_t	cost;
	size_t	pos;
	t_stack	*tmp;

	index = get_pos_target(stack_a, index);
	*index_a = index;
	cost = get_node_position(stack_a, index);
	if (!cost)
		return (0);
	if (cost == 1 && move == 0)
		return (cost - steps);
	else if (cost == 1 && move != 0)
		return (cost);
	else if (cost <= (lst_size(stack_a) / 2) && move == 1 && cost)
		return (cost - steps);
	else if (cost <= (lst_size(stack_a) / 2) && move != 1 && cost)
		return (cost);
	else if (move == 2 && cost)
		return ((lst_size(stack_a) - cost) - steps);
	else if (move != 2 && cost)
		return ((lst_size(stack_a) - cost));
	return (cost);
}

size_t	total_cost(t_stack *stack_a, t_stack *stack_b, size_t index, size_t *index_a)
{
	size_t	cost;

	cost = get_node_position(stack_b, index);
	if (!cost)
		cost += cost_a(stack_a, index, cost, 3, index_a);
	if (cost == 1)
		cost += cost_a(stack_a, index, cost, 0, index_a);
	else if (cost <= (lst_size(stack_b) / 2) && cost)
		cost += cost_a(stack_a, index, cost, 1, index_a);
	else if (cost)
	{
		cost = lst_size(stack_b) - cost;
		cost += cost_a(stack_a, index, cost, 2, index_a);
	}
	return (cost);
}

size_t	cost(t_stack **stack_a, t_stack **stack_b, size_t *index_a)
{
	t_stack *target;
	size_t	index;
	size_t	cost;
	t_stack *iter;
	size_t	test;

	test = 0;
	target = *stack_b;
	index = (*stack_b)->index;
	cost = total_cost(*stack_a, *stack_b, index, &test);
	iter = (*stack_b)->next;
	while (iter)
	{
		if (cost > total_cost(*stack_a, *stack_b, iter->index, &test))
		{
			cost = total_cost(*stack_a, *stack_b, iter->index, index_a);
			target = iter;
		}
		iter = iter->next;
	}
	return (target->index);
}

void	move_both(t_stack **stack_a, t_stack **stack_b, size_t a_p, size_t b_p)
{
	size_t	size_a;
	size_t	size_b;

	size_a = lst_size(*stack_a) / 2;	
	size_b = lst_size(*stack_b) / 2;	
	if (a_p == 1 && b_p == 1)
		swap_a_b(&(*stack_a), &(*stack_b));
	else if (a_p != 1 && b_p == 1)
		swap_b(&(*stack_b), 0);
	else if (a_p && a_p <= size_a && b_p <= size_b)
		rotate_a_b(&(*stack_a), &(*stack_b));
	else if (b_p <= size_b)
		rotate_b(&(*stack_b), 0);
	else if (a_p && a_p > size_a && b_p > size_b)
		reverse_rotate_a_b(&(*stack_a), &(*stack_b));
	else if (b_p > size_b)
		reverse_rotate_b(&(*stack_b), 0);
}

void	move_a(t_stack **stack_a, t_stack **stack_b, size_t a_p)
{
	size_t	size_a;

	size_a = lst_size(*stack_a) / 2;	
	if (a_p == 1)
		swap_a(&(*stack_a), 0);
	else if (a_p <= size_a)
		rotate_a(&(*stack_a), 0);
	else if (a_p > size_a)
		reverse_rotate_a(&(*stack_a), 0);
}

void	moves(t_stack **stack_a, t_stack **stack_b)
{
	size_t	index_a;
	size_t	index_b;

	index_a = 0;
	index_b = cost(&(*stack_a), &(*stack_b), &index_a);
	while ((*stack_b)->index != index_b)
		move_both(&(*stack_a), &(*stack_b), get_node_position(*stack_a, index_a), get_node_position(*stack_b, index_b));
	while ((*stack_a)->index != index_a)
		move_a(&(*stack_a), &(*stack_b), get_node_position(*stack_a, index_a));
	push_a(&(*stack_a), &(*stack_b));
}
