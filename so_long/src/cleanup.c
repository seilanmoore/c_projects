/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:05:31 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/16 22:59:28 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
		ft_mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		ft_mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		ft_mlx_destroy_display(data->mlx_ptr);
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
