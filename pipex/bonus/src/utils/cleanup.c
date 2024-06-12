/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:01:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/12 20:45:07 by smoore-a         ###   ########.fr       */
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

static void	free_cmd(t_data *data)
{
	int	i;

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
	}
}

static void	close_fds(t_data *data)
{
	int	i;

	if (data->here_doc_exists)
	{
		close(data->pipedes[0]);
		close(data->pipedes[1]);
	}
	else
	{
		i = -1;
		while (data->pipes[++i].fd[0] != 0)
		{
			close(data->pipes[i].fd[0]);
			close(data->pipes[i].fd[1]);
		}
	}
	close(data->fd[0]);
	close(data->fd[1]);
}

void	cleanup(t_data *data)
{
	if (data)
	{
		close_fds(data);
		unlink(_HERE_DOC);
		free_strings(&(data->paths));
		free_cmd(data);
		*data = (t_data){0};
	}
}
