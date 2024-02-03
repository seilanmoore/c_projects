/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:11:52 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/03 13:12:46 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*new_node(int number)
{
	t_stack	*new_node;

	new_node = (t_stack *)malloc(sizeof(t_stack));
	if (!new_node)
		return (NULL);
	new_node->index = -1;
	new_node->number = number;
	new_node->next = NULL;
	return (new_node);
}

t_stack	*lst_last(t_stack *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_add_back(t_stack **lst, t_stack *new)
{
	if (lst && new)
	{
		if (*lst)
			lst_last(*lst)->next = new;
		else
			*lst = new;
	}
}

void	lst_clear(t_stack **lst)
{
	t_stack	*current;
	t_stack	*next;

	if (*lst)
	{
		current = *lst;
		while (current)
		{
			next = current->next;
			free(current);
			current = next;
		}
		*lst = NULL;
	}
}

int	lst_size(t_stack *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/* void	lst_print(t_stack *lst_a, t_stack *lst_b)
{
	while (lst_a || lst_b)
	{
		if (lst_a && lst_b)
		{
			printf("	[%d]	[%d]	[%d]		[%d]\n",
			lst_a->number, lst_b->number, lst_a->index, lst_b->index);
			lst_a = lst_a->next;
			lst_b = lst_b->next;
		}
		else if (lst_b)
		{
			printf("		[%d]				[%d]\n",
			lst_b->number, lst_b->index);
			lst_b = lst_b->next;
		}
		else
		{
			printf("	[%d]		[%d]	\n",
			lst_a->number, lst_a->index);
			lst_a = lst_a->next;
		}
	}
	printf("	-----	-----	--------	--------\n");
	printf("	[A]	[B]	[INDEX_A]	[INDEX_B]\n");
} */
