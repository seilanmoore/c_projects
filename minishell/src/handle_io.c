/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:32:54 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/10 21:24:35 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	replace_in_fd(t_data *data)
{
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
	{
		close(data->fd[0]);
		return (1);
	}
	close(data->fd[0]);
	return (0);
}

static int	replace_in_pipe(t_data *data)
{
	close(data->l_pipe[1]);
	if (dup2(data->l_pipe[0], STDIN_FILENO) == -1)
	{
		close(data->l_pipe[0]);
		return (1);
	}
	close(data->l_pipe[0]);
	return (0);
}

static int	replace_out_fd(t_data *data)
{
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	{
		close(data->fd[1]);
		return (1);
	}
	close(data->fd[1]);
	return (0);
}

static int	replace_out_pipe(t_data *data)
{
	close(data->r_pipe[0]);
	if (dup2(data->r_pipe[1], STDOUT_FILENO) == -1)
	{
		close(data->r_pipe[1]);
		return (1);
	}
	close(data->r_pipe[1]);
	return (0);
}

int	handle_io(t_data *data)
{
	if (data->fd[0] != -1)
	{
		if (replace_in_fd(data) == 1)
			return (1);
	}
	else if (data->l_pipe[0] != -1)
	{
		if (replace_in_pipe(data) == 1)
			return (1);
	}
	if (data->fd[1] != -1)
	{
		if (replace_out_fd(data) == 1)
			return (1);
	}
	else if (data->r_pipe[1] != -1)
	{
		if (replace_out_pipe(data) == 1)
			return (1);
	}
	return (0);
}
