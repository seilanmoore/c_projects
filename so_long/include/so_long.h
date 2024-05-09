/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:50:51 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/06 13:03:12 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/include/libft.h"
# include "../mlx_linux/mlx.h"

# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <errno.h>

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR -1
# define WINDOW_WIDTH 500
# define WINDOW_HEIGHT 500
# define SIDE 25

// COLORS

# define WHITE			0x00FFFFFF
# define GRAY			0x007F7F7F
# define BLACK			0x00000000
# define RED			0x00FF0000
# define GREEN			0x0000FF00
# define BLUE			0x000000FF
# define ORANGE			0x00FF7F00
# define YELLOW			0x00FFFF00
# define SPRING_GREEN	0x0000FF7F
# define CYAN			0x0000FFFF
# define MAGENTA		0x00FF00FF
# define ROSE			0x00FF007F
# define PURPLE			0x007F00FF

typedef struct	s_vars
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	m;
	int dx;
	int dy;
	
}	t_vars;

typedef struct	s_lvar
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int x;
	int y;
	int e2;
}	t_lvar;

typedef struct	s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;

typedef struct	s_line
{
	int		x;
	int		y;
	int		length;
	int		angle;
	int		color;
}	t_line;

typedef struct s_point
{
	int	height;
	int	color;
}	t_point;


typedef struct	s_mtrx
{
	t_point	**point;
	char	***map;
	char	*file;
	int		row;
	int		col;
}	t_mtrx;

typedef struct	s_components
{
	int	collec;
	int	exit;
	int	start;
}				t_components;

void	ft_mlx_destroy_window(void *mlx_ptr, void *win_ptr);
void	ft_mlx_destroy_image(void *mlx_ptr, void *mlx_img);
void	ft_mlx_destroy_display(void *mlx_ptr);
void	ft_mlx_loop(t_data *data, void *mlx_ptr);
void	ft_mlx_hook(t_data *data, void *win, int x_event,
	int x_mask,	int (*funct)(),void *param);

void	ft_error(t_data *data, char *message, char *file);
char	**handle_args(int	argc, char **argv);
void	free_map(char ***map);

//void	check_map(char **map);

#endif