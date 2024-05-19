/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:05:31 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 23:34:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	data_error(t_data *data, char *message, char *file)
{
	if (message && !file)
		ft_printf("ERROR: %s\n", message);
	else if (message && file)
		ft_printf("ERROR: %s -- FILE: %s\n", message, file);
	else if (file && !message)
		ft_printf("ERROR: %s -- FILE: %s\n", strerror(errno), file);
	else
		ft_printf("ERROR: %s\n", strerror(errno));
	terminate(data);
}

static void	map_error(t_map *map, char *message)
{
	if (message && !map->fn)
		ft_printf("ERROR: %s\n", message);
	else if (message && map->fn)
		ft_printf("FILE:\t%s\nERROR:\t%s\n", map->fn, message);
	else if (map->fn && !message)
		ft_printf("FILE:\t%s\nERROR:\t%s\n", map->fn, strerror(errno));
	else
		ft_printf("ERROR: %s\n", strerror(errno));
	if (map->mtrx)
		free_map(map->mtrx);
	if (map->fd != NONE)
		close(map->fd);
}

void	free_map(char **map)
{
	int	i;

	if (map == NULL)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	terminate(t_data *data)
{
	if (data)
	{
		if (data->map.mtrx)
			free_map(data->map.mtrx);
		if (data->mlx)
		{
			if (data->mlx_win)
				mlx_destroy_window(data->mlx, data->mlx_win);
			mlx_destroy_display(data->mlx);
		}
	}
}

void	ft_error(t_data *data, t_map *map, char *message)
{
	if (data && map)
	{
		data_error(data, message, map->fn);
		map_error(map, message);
	}
	else if (map)
		map_error(map, message);
	else if (data)
		data_error(data, message, NULL);
	else
		ft_printf("ERROR: %s\n", strerror(errno));
	exit(EXIT_FAILURE);
}
