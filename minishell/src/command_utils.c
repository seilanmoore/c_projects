/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:52:01 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/05 14:12:42 by smoore-a         ###   ########.fr       */
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

t_cmd	*new_cmd(void *command, char **arguments, int builtin)
{
	t_cmd	*new_node;

	if (!command)
		return (NULL);
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->cmd = command;
	new_node->args = arguments;
	new_node->builtin = builtin;
	return (new_node);
}
