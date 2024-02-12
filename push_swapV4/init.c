/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:41:40 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/06 11:39:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_stack_a(t_stack **stack_a, int argc, char **argv)
{
	int		i;
	t_stack	*tmp;

	i = 0;
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
