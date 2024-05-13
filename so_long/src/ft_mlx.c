/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 05:00:41 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/13 19:01:39 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/*
void	terminate(t_data *data)
{
	if (data)
	{
		ft_mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		ft_mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		ft_mlx_destroy_display(data->mlx_ptr);
	}
}

t_data	init_data()
{
	t_data	data;
	data.mlx_ptr = NULL;
	data.win_ptr = NULL;
	data.img = (t_img){NULL, NULL, 0, 0, 0};
	return(data);
}

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)dst = color;
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			ft_mlx_pixel_put(img, j++, i, color);
		}
		++i;
	}
}

int	render_line(t_img *img, t_line line)
{
	t_vars	var;
	int		dx;
	int		dy;
	int		err;
	int		x;
	int		y;
	int		e2;

	var = (t_vars){0, 0, 0, 0, 0};
	while (var.i <= (int)(line.length * -sin(M_PI * line.angle / 180))
		&& (line.y + var.i) <= WINDOW_HEIGHT)
	{
		var.j = 0;
		while (var.j <= (int)(line.length * cos(M_PI * line.angle / 180))
			&& (line.x + var.j) <= WINDOW_WIDTH)
		{
			ft_mlx_pixel_put(img, line.x + var.j,
				line.y + var.i, line.color);
			var.j++;
		}
		var.i++;
	}
	return (0);
}

void	gradient(t_line line);

void	print_line(t_img *img, t_line line, t_lvar v)
{
	while ((v.x != line.x + v.dx || v.y != line.y + v.dy)
		&& v.y <= WINDOW_HEIGHT
		&& v.x <= WINDOW_WIDTH)
	{
		ft_mlx_pixel_put(img, v.x, v.y, line.color);
		v.e2 = 2 * v.err;
		if (v.e2 > -v.dy)
		{
			v.err -= v.dy;
			v.x += v.sx;
		}
		if (v.e2 < v.dx)
		{
			v.err += v.dx;
			v.y += v.sy;
		}
	}
}

int	render_line(t_img *img, t_line line)
{
	t_lvar	v;

	if (line.angle < 0 || line.angle > 90)
		line.angle = abs(line.angle % 90);
	v.dx = abs((int)(line.length * cos(M_PI * line.angle / 180)));
	v.dy = abs((int)(line.length * sin(M_PI * line.angle / 180)));
	if (line.length * cos(M_PI * line.angle / 180) >= 0)
		v.sx = 1;
	else
		v.sx = -1;
	if (line.length * sin(M_PI * line.angle / 180) >= 0)
		v.sy = 1;
	else
		v.sy = -1;
	v.err = v.dx - v.dy;
	v.x = line.x;
	v.y = line.y;
	print_line(img, line, v);
	return (0);
}

int render_mtrx(t_img *img, t_mtrx mtrx)
{
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	ft_printf("Keypress: %d\n", keysym);
	if (keysym == XK_Escape)
	{
		terminate(data);
		exit(EXIT_SUCCESS);
	}
	else if (keysym == XK_b)
	{
		render_background(&data->img, GREEN);
		mlx_put_image_to_window(
			data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	}
	else if (keysym == XK_a)
	{
		render_line(&data->img, (t_line){300, 300, 100, 0, WHITE});
		mlx_put_image_to_window(
			data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	}
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	ft_printf("Keyrelease: %d\n", data->img.line_len);
	return (0);
}
int	render(t_data *data)
{
	if (!data->win_ptr)
		return (1);
	render_background(&data->img, WHITE);
	mlx_put_image_to_window(
		data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
} */

void	ft_error(t_data *data, char *message, char *file)
{
	if (message && !file)
		ft_printf("ERROR: %s\n", message);
	else if (message && file)
		ft_printf("ERROR: %s -- FILE: %s\n", message, file);
	else if (file && !message)
		ft_printf("ERROR: %s -- FILE: %s\n", strerror(errno), file);
	else
		ft_printf("ERROR: %s\n", strerror(errno));
	//terminate(data);
	data->mlx_ptr = NULL;
	exit(EXIT_FAILURE);
}

/* int	close_window_hook(t_data *data)
{
	terminate(data);
	exit(EXIT_SUCCESS);
}

void	init_window(void)
{
	t_data	data;

	data = init_data();
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		ft_error(NULL, "Could'nt initiate mlx", NULL);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Program");
	if (!data.win_ptr)
		ft_error(&data, "Could'nt create new window", NULL);
	data.img.mlx_img =
		mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data.img.mlx_img)
		ft_error(&data, "Could'nt create new image", NULL);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	// mlx_loop_hook(data.mlx_ptr, &render, &data);
	ft_mlx_hook(&data, data.win_ptr, KeyPress,
		KeyPressMask, &handle_keypress, &data);
	ft_mlx_hook(&data, data.win_ptr, DestroyNotify,
	NoEventMask, &close_window_hook, &data);
	ft_mlx_loop(&data, data.mlx_ptr);
}

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
} */