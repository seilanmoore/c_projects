/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 05:00:41 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/22 23:19:54 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <X11/X.h>

void	key_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		terminate(data);
	if (keycode == XK_Up)
		mlx_clear_window(data->mlx, data->mlx_win);
}

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_error(data, "Could'nt initialize mlx");
	data->mlx_win = mlx_new_window(
			data->mlx, data->map.width * TILE_SIZE,
			data->map.height * TILE_SIZE, "So_long");
	if (!data->mlx_win)
		ft_error(data, "Could'nt create new window");
	convert_xpm(data);
	mlx_hook(data->mlx_win, DESTROY_NOTIF,
		NO_EVENT_MASK, (void *)terminate, data);
	mlx_key_hook(data->mlx_win, (void *)key_hook, data);
	mlx_expose_hook(data->mlx_win, (void *)draw_map, data);
	mlx_loop(data->mlx);
}
