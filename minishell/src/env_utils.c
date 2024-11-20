/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:03:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/28 13:40:59 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

void	print_env(t_data *data)
{
	void	*head;

	head = data->env;
	while (data->env)
	{
		printf("VARIABLE: \'%s\'\nVALUE: \'%s\'\n", \
		data->env->variable, data->env->value);
		data->env = data->env->next;
	}
	data->env = head;
}

static void	del_node(t_env **lst, t_env *node)
{
	ft_free(&(node->variable));
	ft_free(&(node->value));
	free(node);
	*lst = NULL;
}

void	del_env(t_env **env, char *variable)
{
	t_env	*head;
	t_env	*current;

	head = *env;
	current = (*env)->next;
	if (!current)
	{
		del_node(env, head);
		return ;
	}
	while (current)
	{
		if (!ft_strcmp(current->variable, variable))
		{
			(*env)->next = current->next;
			del_node(&(current), current);
		}
		else
		{
			*env = (*env)->next;
			current = current->next;
		}
	}
	*env = head;
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

t_env	*get_env_var(t_env *env, char *variable)
{
	t_env	*head;

	if (!env || !variable)
		return (NULL);
	head = env;
	while (env)
	{
		if (!ft_strcmp(env->variable, variable))
			return (env);
		env = env->next;
	}
	env = head;
	return (NULL);
}
