/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:01:02 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/23 11:31:21 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	xpm_to_img(t_data *data, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(
			data->mlx, path, &(texture->width), &(texture->height));
	if (!texture->img)
		ft_error(data, "Failed to convert xpm");
}

void	convert_xpm(t_data *data)
{
	data->texture.border.width = TILE_SIZE;
	data->texture.border.height = TILE_SIZE;
	xpm_to_img(data, &(data->texture.border), "textures/border.xpm");
	data->texture.collectible.width = TILE_SIZE;
	data->texture.collectible.height = TILE_SIZE;
	xpm_to_img(data, &(data->texture.collectible), "textures/meat.xpm");
	data->texture.ground.width = TILE_SIZE;
	data->texture.ground.height = TILE_SIZE;
	xpm_to_img(data, &(data->texture.ground), "textures/ground.xpm");
	data->texture.exit.width = TILE_SIZE;
	data->texture.exit.height = TILE_SIZE;
	xpm_to_img(data, &(data->texture.exit), "textures/tower.xpm");
	data->texture.player.width = TILE_SIZE;
	data->texture.player.height = TILE_SIZE;
	xpm_to_img(data, &(data->texture.player), "textures/player.xpm");
}
