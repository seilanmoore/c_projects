/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:07 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/26 18:38:35 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

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
		free(data->locals->variable);
		data->locals->variable = NULL;
		free(data->locals->value);
		data->locals->value = NULL;
		tmp = data->locals;
		data->locals = data->locals->next;
		free(tmp);
	}
}

void	free_env_lst(t_data *data)
{
	t_env	*tmp;

	while (data->env)
	{
		free(data->env->variable);
		data->env->variable = NULL;
		free(data->env->value);
		data->env->value = NULL;
		tmp = data->env;
		data->env = data->env->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_environment(t_data *data)
{
	free_env_lst(data);
	free_array(&(data->envp));
}

void	free_cmds(t_data *data)
{
	t_cmd	*tmp;

	while (data->input.command)
	{
		free(data->input.command->cmd);
		data->input.command->cmd = NULL;
		free_array(&(data->input.command->args));
		tmp = data->input.command;
		data->input.command = data->input.command->next;
		free(tmp);
	}
}

void	free_tokens(t_data *data)
{
	t_token	*tmp;

	while (data->input.tokens)
	{
		free(data->input.tokens->token);
		data->input.tokens->token = NULL;
		tmp = data->input.tokens;
		data->input.tokens = data->input.tokens->next;
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	t_env	*env_head;
	t_env	*local_head;
	char	**env_ptr;
	char	*aux;
	char	*proc;

	aux = data->prev_exit_code;
	env_head = data->env;
	env_ptr = data->envp;
	local_head = data->locals;
	proc = data->process;
	ft_free(&(data->prompt));
	ft_free(&(data->input.raw_line));
	ft_free(&(data->history));
	ft_free(&(data->cwd));
	free_tokens(data);
	free_cmds(data);
	free_array(&(data->paths));
	*data = (t_data){0};
	data->locals = (t_env *){0};
	data->input = (t_input){0};
	data->env = env_head;
	data->envp = env_ptr;
	data->locals = local_head;
	data->process = proc;
	free(data->prev_exit_code);
	data->prev_exit_code = aux;
}
