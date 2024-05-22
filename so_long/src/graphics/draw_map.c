/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:27:28 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/22 13:01:53 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/* void	put_image(t_data *data, int x, int y)
{
	char	*addr;

	addr = mlx_get_data_addr(
		data->, int *bits_per_pixel, int *size_line, int *endian)
} */

void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map.mtrx[++i])
	{
		j = -1;
		while (data->map.mtrx[i][++j])
		{
			if (data->map.mtrx[i][j] == '0')
				draw_ground(data, j, i);
			else if (data->map.mtrx[i][j] == '1')
				draw_border(data, j, i);
			else if (data->map.mtrx[i][j] == 'C')
				draw_collectible(data, j, i);
			else if (data->map.mtrx[i][j] == 'E')
				draw_exit(data, j, i);
			else if (data->map.mtrx[i][j] == 'P')
				draw_player(data, j, i);
		}
	}
}
