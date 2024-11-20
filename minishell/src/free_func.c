/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:07 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/10 21:44:13 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	free_environment(t_data *data)
{
	free_env_lst(data);
	free_array(&(data->envp));
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

static void	reset_var(t_data *data)
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
