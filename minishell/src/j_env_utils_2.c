/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_env_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:03:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/12 12:17:35 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

t_env	*new_variable(char *variable, char *value)
{
	t_env	*new_node;

	if (!variable)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->variable = ft_strdup(variable);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = ft_strdup("");
	new_node->next = NULL;
	return (new_node);
}

t_env	*last_variable(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back_variable(t_env **lst, t_env *node)
{
	if (lst && node)
	{
		if (*lst)
			last_variable(*lst)->next = node;
		else
			*lst = node;
	}
}

int	env_size(t_env *lst)
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

void	upd_env(t_data *data)
{
	free_array(&(data->envp));
	envp_to_array(data);
}
