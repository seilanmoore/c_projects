/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:03:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/03 15:10:12 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*last_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back_token(t_token **lst, t_token *node)
{
	if (lst && node)
	{
		if (*lst)
			last_token(*lst)->next = node;
		else
			*lst = node;
	}
}

t_token	*new_token(void *token, int type, int quote)
{
	t_token	*new_node;

	if (!token)
		return (NULL);
	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->token = token;
	new_node->type = type;
	new_node->quote = quote;
	new_node->opt = NULL;
	new_node->arg = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}
