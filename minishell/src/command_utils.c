/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:52:01 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/30 12:13:00 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*last_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back_cmd(t_cmd **lst, t_cmd *node)
{
	if (lst && node)
	{
		if (*lst)
			last_cmd(*lst)->next = node;
		else
			*lst = node;
	}
}

t_cmd	*new_cmd(t_token *token, char **arguments, int builtin)
{
	t_cmd	*new_node;

	if (!token)
		return (NULL);
	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->cmd = ft_strdup(token->token);
	if (!(new_node->cmd))
	{
		free(new_node);
		return (NULL);
	}
	new_node->args = arguments;
	new_node->builtin = builtin;
	new_node->token = token;
	return (new_node);
}
