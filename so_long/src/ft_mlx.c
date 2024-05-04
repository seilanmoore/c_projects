/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 05:00:41 by smoore-a          #+#    #+#             */
/*   Updated: 2024/03/05 06:36:00 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_mlx_destroy_window(void *mlx_ptr, void *win_ptr)
{
	if (mlx_ptr)
	{
		if (win_ptr)
		{
			mlx_destroy_window(mlx_ptr, win_ptr);
			win_ptr = NULL;
		}
	}
}

void	ft_mlx_destroy_image(void *mlx_ptr, void *mlx_img)
{
	if (mlx_ptr)
	{
		if (mlx_img)
		{
			mlx_destroy_image(mlx_ptr, mlx_img);
			mlx_img = NULL;
		}
	}
}

void	ft_mlx_destroy_display(void *mlx_ptr)
{
	if (mlx_ptr)
	{
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
		mlx_ptr = NULL;
	}
	ft_printf("Process terminated\n");
}

void	ft_mlx_hook(t_data *data, void *win, int x_event,
	int x_mask, int (*funct)(), void *param)
{
	if (param)
	{
		if (win)
			mlx_hook(win, x_event, x_mask, funct, param);
		else
			ft_error(data, "Window not found", NULL);
	}
	else
		ft_error(data, "Display not found", NULL);
}

void	ft_mlx_loop(t_data *data, void *mlx_ptr)
{
	if (mlx_ptr)
		mlx_loop(mlx_ptr);
	else
		ft_error(data, "Display not found", NULL);
}