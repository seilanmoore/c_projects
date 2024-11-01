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
		ft_free(&(data->input.command->cmd));
		free_array(&(data->input.command->args));
		tmp = data->input.command;
		data->input.command = data->input.command->next;
		*tmp = (t_cmd){0};
		free(tmp);
	}
}

void	free_tokens(t_data *data)
{
	t_token	*tmp;

	while (data->input.tokens)
	{
		ft_free(&(data->input.tokens->token));
		tmp = data->input.tokens;
		data->input.tokens = data->input.tokens->next;
		*tmp = (t_token){0};
		free(tmp);
	}
}

void	reset_var(t_data *data)
{
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->l_pipe[0] = -1;
	data->l_pipe[1] = -1;
	data->r_pipe[0] = -1;
	data->r_pipe[1] = -1;
	data->in_cmd = 0;
	data->in_arg = 0;
	data->in_local = 0;
	data->n_cmd = 0;
	data->n_pipe = 0;
	data->n_files = 0;
	data->status = 0;
	data->exit_code = 0;
	data->heredoc = NULL;
	data->input = (t_input){0};
}

void	free_data(t_data *data)
{
	ft_free(&(data->input.raw_line));
	ft_free(&(data->history));
	ft_free(&(data->cwd));
	ft_free(&(data->prompt));
	free_array(&(data->paths));
	free_tokens(data);
	free_cmds(data);
	reset_var(data);
}
