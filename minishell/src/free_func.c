/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:07 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/04 13:15:06 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	free_local(t_data *data)
{
	t_l_var	*tmp;

	while (data->local)
	{
		free(data->local->variable);
		data->local->variable = NULL;
		free(data->local->value);
		data->local->value = NULL;
		tmp = data->local;
		data->local = data->local->next;
		free(tmp);
	}
}

void	free_environment(t_data *data)
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
	}
	free_array(data->envp_cpy);
	data->envp_cpy = NULL;
}

void	free_cmds(t_data *data)
{
	t_cmd	*tmp;

	while (data->input.command)
	{
		free(data->input.command->cmd);
		data->input.command->cmd = NULL;
		free_array(data->input.command->args);
		data->input.command->args = NULL;
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
	int		i;
	t_env	*env_head;
	t_l_var	*local_head;
	char	**env_ptr;
	char	*aux;

	aux = data->prev_exit_code;
	env_head = data->env;
	env_ptr = data->envp_cpy;
	local_head = data->local;
	free(data->prompt);
	free(data->input.raw_line);
	free(data->history);
	free(data->process);
	free(data->cwd);
	free_tokens(data);
	free_cmds(data);
	i = -1;
	if (data->input.command)
	{
		while (data->input.command[++i].cmd)
			free(data->input.command[i].cmd);
		free(data->input.command);
	}
	free_array(data->paths);
	i = data->status;
	init_data(data, data->argc, data->argv, data->envp);
	data->env = env_head;
	data->envp_cpy = env_ptr;
	data->local = local_head;
	data->status = i;
	free(data->prev_exit_code);
	data->prev_exit_code = aux;
}
