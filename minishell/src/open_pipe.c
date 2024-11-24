/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:28:40 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/24 21:43:34 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	change_pipe(t_data *data)
{
	if (data->r_pipe[0] != -1)
	{
		if (!(data->heredoc) && data->fd[0] == -1)
		{
			if (data->l_pipe[0] != -1)
				close(data->l_pipe[0]);
			if (data->l_pipe[1] != -1)
				close(data->l_pipe[1]);
			if (pipe(data->l_pipe) == -1)
				return (1);
			dup2(data->r_pipe[0], data->l_pipe[0]);
			dup2(data->r_pipe[1], data->l_pipe[1]);
		}
		if (data->r_pipe[0] != -1)
			close(data->r_pipe[0]);
		if (data->r_pipe[1] != -1)
			close(data->r_pipe[1]);
		data->r_pipe[0] = -1;
		data->r_pipe[1] = -1;
	}
	data->heredoc = NULL;
	return (0);
}

int	open_r_pipe(t_data *data)
{
	if (data->input.tokens)
	{
		if (data->input.tokens->prev && \
		data->input.tokens->prev->type == PIPE && \
		pipe(data->r_pipe) == -1)
			return (1);
	}
	return (0);
}
