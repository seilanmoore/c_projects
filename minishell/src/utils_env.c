/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:03:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/27 21:20:18 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

static void	del_node(t_environment *env)
{
	free(env->variable);
	env->variable = NULL;
	free(env->value);
	env->value = NULL;
	free(env);
}

void	del_env(t_environment *env, char *variable)
{
	size_t			len;
	t_environment	*head;
	t_environment	*current;

	len = ft_strlen(variable);
	head = env;
	current = env->next;
	if (!current)
		return (del_node(env));
	while (current)
	{
		if (ft_strlen(current->variable) == len && \
			!ft_strncmp(current->variable, variable, len))
		{
			printf("CURRENT->NEXT: %s\n", current->next->variable);
			env->next = current->next;
			del_node(current);
			current = NULL;
		}
		else
		{
			env = env->next;
			current = current->next;
		}
	}
	env = head;
}

int	variable_len(char *envp_line)
{
	int	i;

	i = -1;
	if (!envp_line)
		return (0);
	while (envp_line[++i] != '=')
		;
	return (i);
}

t_environment	*get_env_var(t_environment *env, char *variable)
{
	t_environment	*head;
	size_t			len;

	if (!env || !variable)
		return (NULL);
	len = ft_strlen(variable);
	head = env;
	while (env)
	{
		if (ft_strlen(env->variable) == len && \
			!ft_strncmp(env->variable, variable, len))
			return (env);
		env = env->next;
	}
	env = head;
	return (NULL);
}

t_environment	*new_variable(void *variable, char *value)
{
	t_environment	*new_node;

	if (!variable)
		return (NULL);
	new_node = (t_environment *)malloc(sizeof(t_environment));
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

void	upd_env(t_data *data)
{
	free_array(data->envp_cpy);
	data->envp_cpy = NULL;
	envp_to_array(data);
}
