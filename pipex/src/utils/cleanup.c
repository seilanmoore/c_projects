/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:01:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/12 20:30:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

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
	close(data->fd_in);
	close(data->fd_out);
	close(data->pipedes[0]);
	close(data->pipedes[1]);
}

void	cleanup(t_data *data)
{
	if (data)
	{
		close_fds(data);
		if (data->cmd1p)
			free(data->cmd1p);
		if (data->cmd2p)
			free(data->cmd2p);
		free_strings(&(data->paths));
		free_strings(&(data->cmd1));
		free_strings(&(data->cmd2));
		*data = (t_data){0};
	}
}
