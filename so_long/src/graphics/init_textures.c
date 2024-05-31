/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:01:02 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/26 12:30:35 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	xpm_to_img(t_data *data, t_img *texture, char *path)
{
	int	width;
	int	height;

	width = TILE_SIZE;
	height = TILE_SIZE;
	texture->img = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
	if (!texture->img)
		ft_error(data, "Failed to convert xpm");
}

void	convert_xpm(t_data *data)
{
	xpm_to_img(data, &(data->texture.border), "textures/border.xpm");
	xpm_to_img(data, &(data->texture.collectible), "textures/meat.xpm");
	xpm_to_img(data, &(data->texture.ground), "textures/ground.xpm");
	xpm_to_img(data, &(data->texture.exit), "textures/tower.xpm");
	xpm_to_img(data, &(data->texture.player), "textures/player.xpm");
}
