/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:47:18 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/22 19:44:38 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	draw_ground(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->texture.ground.img, x * TILE_SIZE, y * TILE_SIZE);
}

void	draw_collectible(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->texture.collectible.img, x * TILE_SIZE, y * TILE_SIZE);
}

void	draw_border(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->texture.border.img, x * TILE_SIZE, y * TILE_SIZE);
}

void	draw_exit(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->texture.exit.img, x * TILE_SIZE, y * TILE_SIZE);
}

void	draw_player(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->texture.player.img, x * TILE_SIZE, y * TILE_SIZE);
}
