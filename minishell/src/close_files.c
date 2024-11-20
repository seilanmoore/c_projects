/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:04:05 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/09 15:19:01 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_infiles(t_data *data)
{
	if (data->fd[0] != -1)
		close(data->fd[0]);
	if (data->r_pipe[0] != -1)
		close(data->r_pipe[0]);
	if (data->r_pipe[1] != -1)
		close(data->r_pipe[1]);
	data->r_pipe[0] = -1;
	data->r_pipe[1] = -1;
	if (data->l_pipe[0] != -1)
		close(data->l_pipe[0]);
	if (data->l_pipe[1] != -1)
		close(data->l_pipe[1]);
	data->l_pipe[0] = -1;
	data->l_pipe[1] = -1;
}

void	close_parent_files(t_data *data)
{
	if (data->l_pipe[0] != -1)
		close(data->l_pipe[0]);
	if (data->l_pipe[1] != -1)
		close(data->l_pipe[1]);
	data->l_pipe[0] = -1;
	data->l_pipe[1] = -1;
	if (data->fd[0] != -1)
		close(data->fd[0]);
	if (data->fd[1] != -1)
		close(data->fd[1]);
	data->fd[0] = -1;
	data->fd[1] = -1;
}
