/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 05:00:41 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 12:41:48 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->img = (t_img){NULL, NULL, 0, 0, 0};
}
void	init_window(t_data *data)
{
	init_data(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_error(NULL, NULL, "Could'nt initiate mlx");
	data->mlx_win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Program");
	if (!data->mlx_win)
		ft_error(data, NULL, "Could'nt create new window");
}
