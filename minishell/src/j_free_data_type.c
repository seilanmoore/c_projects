/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:07 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/01 14:48:55 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_array(char ***array)
{
	int	i;

	i = -1;
	if (!(*array))
		return ;
	while ((*array)[++i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
	}
	free(*array);
	*array = NULL;
}

void	free_local(t_data *data)
{
	t_env	*tmp;

	while (data->locals)
	{
		ft_free(&(data->locals->variable));
		ft_free(&(data->locals->value));
		tmp = data->locals;
		data->locals = data->locals->next;
		*tmp = (t_env){0};
		free(tmp);
	}
}

void	free_env_lst(t_data *data)
{
	t_env	*tmp;

	while (data->env)
	{
		ft_free(&(data->env->variable));
		ft_free(&(data->env->value));
		tmp = data->env;
		data->env = data->env->next;
		*tmp = (t_env){0};
		free(tmp);
	}
}

void	free_cmds(t_data *data)
{
	t_cmd	*tmp;

	while (data->input.command)
	{
		ft_free(&(data->input.command->cmd));
		free_array(&(data->input.command->args));
		tmp = data->input.command;
		data->input.command = data->input.command->next;
		*tmp = (t_cmd){0};
		free(tmp);
	}
}

//From expand.c
void	free_lst(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		free((*lst)->content);
		(*lst)->content = NULL;
		*lst = (*lst)->next;
		free(tmp);
	}
	free(*lst);
	*lst = NULL;
}
