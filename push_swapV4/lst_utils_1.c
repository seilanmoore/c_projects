/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:11:52 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/06 19:22:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*new_node(int number)
{
	t_stack	*new_node;

	new_node = (t_stack *)malloc(sizeof(t_stack));
	if (!new_node)
		return (NULL);
	new_node->index = 0;
	new_node->number = number;
	new_node->indexed = 0;
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
	if (!new)
		return ;
	if (*lst)
		lst_last(*lst)->next = new;
	else
		*lst = new;
}

void	lst_clear(t_stack **lst)
{
	t_stack	*next;
	t_stack	*current;

	if (!(*lst))
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

size_t	lst_size(t_stack *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
