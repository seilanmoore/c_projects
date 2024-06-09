/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:01:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/09 10:45:43 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	free_strings(char ***str)
{
	int	i;

	if (*str)
	{
		i = -1;
		while ((*str)[++i])
		{
			free((*str)[i]);
			(*str)[i] = NULL;
		}
		free(*str);
		*str = NULL;
	}
}

static void	close_fds(t_data *data)
{
	if (data->file[0].fd != ERROR)
	{
		if (close(data->file[0].fd) == ERROR)
			ft_error(data, CLOSEF, strerror(errno));
		data->file[0].fd = -1;
	}
	if (data->file[1].fd != ERROR)
	{
		if (close(data->file[1].fd) == ERROR)
			ft_error(data, CLOSEF, strerror(errno));
		data->file[1].fd = -1;
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
	int	i;

	if (data)
	{
		close_fds(data);
		free_strings(&(data->paths));
		if (data->cmd)
		{
			i = -1;
			while (&(data->cmd[++i]) != NULL)
			{
				free_strings(&(data->cmd[i].opt));
				free(data->cmd->path);
			}
			free(data->cmd);
		}
		if (data->file[0].name)
			free(data->file[0].name);
		if (data->file[1].name)
			free(data->file[1].name);
		*data = (t_data){0};
	}
}
