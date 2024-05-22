/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:01:02 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/22 19:44:10 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	xpm_to_img(t_data *data, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(
			data->mlx, path, &(texture->width), &(texture->height));
	if (!texture->img)
		ft_error(data, "Failed to convert xpm");
}

void	convert_xpm(t_data *data)
{
	int	width;
	int	height;

	width = TILE_SIZE;
	height = TILE_SIZE;
	data->texture.border.img = mlx_xpm_file_to_image(
			data->mlx, "textures/border.xpm", &width, &height);
	data->texture.collectible.img = mlx_xpm_file_to_image(
			data->mlx, "textures/meat.xpm", &width, &height);
	data->texture.ground.img = mlx_xpm_file_to_image(
			data->mlx, "textures/ground.xpm", &width, &height);
	data->texture.exit.img = mlx_xpm_file_to_image(
			data->mlx, "textures/tower.xpm", &width, &height);
	data->texture.player.img = mlx_xpm_file_to_image(
			data->mlx, "textures/player.xpm", &width, &height);
}
