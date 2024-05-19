/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:50:51 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 23:32:43 by smoore-a         ###   ########.fr       */
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
# define NONE 0
# define FALSE 0
# define SUCCESS 0
# define ERROR -1
# define WINDOW_WIDTH 500
# define WINDOW_HEIGHT 500
# define SIDE 25
# define NOTVALID "invalid map"

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

typedef struct s_sprite
{
	void	*border;
	void	*ground;
	void	*exit;
	void	*collectible;
	void	*player_stand[5];
	void	*player_moves[5];
}	t_sprite;

typedef struct s_map
{
	char	*fn;
	int		fd;
	char	**mtrx;
	size_t	width;
	size_t	height;
	size_t	collecs;
	size_t	exits;
	size_t	player;
	size_t	walls;
	size_t	spaces;
}	t_map;

typedef struct s_player
{
	size_t	y;
	size_t	x;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_sprite	sprite;
	t_map		map;
}	t_data;

// utils
void	print_map(char **map);
//init_window
void	init_window(t_data *data);
// parse_file
void	print_map(char **map);
void	parse_file(t_map *map, int argc, char **argv);
// cleanup
void	free_map(char **map);
void	terminate(t_data *data);
void	ft_error(t_data *data, t_map *map, char *message);
// check_map
int		check_sections(t_map *map, char *line);
void	check_map(t_map *map);
// check_path
void	get_player_coord(t_player *coord, char **map);
char	**ft_mtrxdup(char **mtrx);
void	check_path(t_map *map);
// open_close_file
void	openf(t_map *map);
void	closef(t_map *map);

#endif