/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:03:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/22 12:41:15 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_environment	*new_variable(void *variable, char *value)
{
	t_environment	*new_node;

	if (!variable)
		return (NULL);
	new_node = (t_environment *)malloc(sizeof(t_environment));
	if (!new_node)
		return (NULL);
	new_node->variable = variable;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_environment	*last_variable(t_environment *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back_variable(t_environment **lst, t_environment *node)
{
	if (lst && node)
	{
		if (*lst)
			last_variable(*lst)->next = node;
		else
			*lst = node;
	}
}

void	add_front_variable(t_environment **lst, t_environment *node)
{
	if (lst && node)
	{
		node->next = *lst;
		*lst = node;
	}
}

int	env_size(t_environment *lst)
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
