/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:01:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/30 17:14:21 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	free_strings(char **str)
{
	int	i;

	if (str)
	{
		i = -1;
		while (str[++i])
		{
			free(str[i]);
			str[i] = NULL;
		}
		free(str);
		str = NULL;
	}
}

static void	close_fds(t_data *data)
{
	if (data->fd_in != ERROR)
	{
		if (close(data->fd_in) == ERROR)
			ft_error(data, CLOSEF, strerror(errno));
		data->fd_in = -1;
	}
	if (data->fd_out != ERROR)
	{
		if (close(data->fd_out) == ERROR)
			ft_error(data, CLOSEF, strerror(errno));
		data->fd_out = -1;
	}
	if (data->pipedes[0] != ERROR)
	{
		if (close(data->pipedes[0]) == ERROR)
			ft_error(data, CLOSEF, strerror(errno));
		data->pipedes[0] = -1;
	}
	if (data->pipedes[1] != ERROR)
	{
		if (close(data->pipedes[1]) == ERROR)
			ft_error(data, CLOSEF, strerror(errno));
		data->pipedes[1] = -1;
	}
}

void	cleanup(t_data *data)
{
	if (data)
	{
		close_fds(data);
		free(data->cmd1p);
		free(data->cmd2p);
		free_strings(data->cmd1);
		free_strings(data->cmd2);
		free_strings(data->paths);
	}
}
