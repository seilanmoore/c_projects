/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:41:40 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/14 22:31:06 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

size_t	get_node_pos(t_stack *stack, int number)
{
	size_t	pos;

	pos = 0;
	while (stack->number != number)
	{
		stack = stack->next;
		pos++;
	}
	return (pos);
}

size_t	get_index(t_stack *stack)
{
	int		min;
	t_stack	*tmp;

	tmp = stack;
	while (tmp->indexed)
		tmp = tmp->next;
	min = tmp->number;
	tmp = tmp->next;
	while (tmp)
	{
		if (min > tmp->number && !(tmp->indexed))
			min = tmp->number;
		tmp = tmp->next;
	}
	return (get_node_pos(stack, min));
}

void	init_stack_a(t_stack **stack_a, int argc, char **argv)
{
	int		i;
	t_stack	*tmp;

	i = -1;
	while (++i < argc)
	{
		tmp = new_node(atol(argv[i]));
		if (!tmp)
		{
			lst_clear(&(*stack_a));
			return ;
		}
		lst_add_back(&(*stack_a), tmp);
	}
}

void	index_stack(t_stack **stack_a)
{
	size_t	i;
	size_t	pos;
	size_t	size;
	t_stack	*tmp;

	i = 0;
	tmp = (*stack_a);
	size = lst_size(*stack_a);
	while (i < size)
	{
		tmp = *stack_a;
		pos = get_index(*stack_a);
		while (pos-- > 0)
			tmp = tmp->next;
		tmp->index = i;
		tmp->indexed = 1;
		i++;
	}
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}
