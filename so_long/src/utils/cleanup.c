/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:05:31 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/23 12:39:44 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

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

static void	destroy_imgs(t_data *data)
{
	if (data->texture.border.img)
		mlx_destroy_image(data->mlx, data->texture.border.img);
	if (data->texture.collectible.img)
		mlx_destroy_image(data->mlx, data->texture.collectible.img);
	if (data->texture.exit.img)
		mlx_destroy_image(data->mlx, data->texture.exit.img);
	if (data->texture.ground.img)
		mlx_destroy_image(data->mlx, data->texture.ground.img);
	if (data->texture.player.img)
		mlx_destroy_image(data->mlx, data->texture.player.img);
}

void	terminate(t_data *data)
{
	if (data)
	{
		if (data->map.fd != ERROR)
			closef(data);
		if (data->map.mtrx)
			free_map(data->map.mtrx);
		if (data->mlx)
		{
			destroy_imgs(data);
			if (data->mlx_win)
				mlx_destroy_window(data->mlx, data->mlx_win);
			mlx_destroy_display(data->mlx);
			free(data->mlx);
			data->mlx = NULL;
		}
	}
	exit(EXIT_SUCCESS);
}
