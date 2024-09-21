/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:03:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/21 18:41:47 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lst_size(t_tokens *lst)
{
	int	lst_len;

	lst_len = 0;
	while (lst)
	{
		lst = lst->next;
		lst_len++;
	}
	return (lst_len);
}

void	add_front_token(t_tokens **lst, t_tokens *node)
{
	if (lst && node)
	{
		node->next = *lst;
		*lst = node;
	}
}

t_tokens	*last_token(t_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back_token(t_tokens **lst, t_tokens *node)
{
	if (lst && node)
	{
		if (*lst)
			last_token(*lst)->next = node;
		else
			*lst = node;
	}
}

t_tokens	*new_token(void *token, int type)
{
	t_tokens	*new_node;

	new_node = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_node)
		return (NULL);
	new_node->token = token;
	new_node->type = type;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}
