/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:01:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/10 19:52:39 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	close_file(t_data *data, t_file *file)
{
	if (file != NULL)
	{
		file->opened = 0;
		file->closed = 1;
	}
	if (close(file->fd) == ERROR)
		ft_error(data, CLOSEF, strerror(errno));
}
void	close_pipe(t_data *data, t_pipedes *pipedes, int in_out)
{
	if (pipedes != NULL)
	{
		pipedes->opened[in_out] = 0;
		pipedes->closed[in_out] = 1;
	}
	if (close(pipedes->fd[in_out]) == ERROR)
		ft_error(data, CLOSEF, strerror(errno));
}

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
	if (data->file[0].opened && !data->file[0].closed)
		close_file(data, &(data->file[0]));
	if (data->file[1].opened && !data->file[1].closed)
		close_file(data, &(data->file[1]));
	if (data->pipedes.opened[0] && !data->pipedes.closed[0])
		close_pipe(data, &(data->pipedes), 0);
	if (data->pipedes.opened[1] && !data->pipedes.closed[1])
		close_pipe(data, &(data->pipedes), 1);
}

void	cleanup(t_data *data)
{
	int	i;

	if (data)
	{
		close_fds(data);
		unlink(_HERE_DOC);
		free_strings(&(data->paths));
		if (data->cmd)
		{
			i = -1;
			while (data->cmd[++i].opt)
			{
				free_strings(&(data->cmd[i].opt));
				if (data->cmd[i].path)
					free(data->cmd[i].path);
			}
			free(data->cmd);
			data->cmd = (t_cmd *){0};
		}
		*data = (t_data){0};
	}
}
