/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:53:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/17 13:42:39 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_sections(t_map *map, char *line)
{
	while (*line && *line != '\n')
	{
		if (*line == 'C')
			map->collecs++;
		else if (*line == 'E')
			map->exits++;
		else if (*line == 'P')
			map->player++;
		else if (*line == '1')
			map->walls++;
		else if (*line == '0')
			map->spaces++;
		else
			return (ERROR);
		line++;
	}
	return (SUCCESS);
}

static void	check_wall(t_map *map)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < map->width)
	{
		if (map->mtrx[0][j] != '1' || map->mtrx[map->height - 1][j] != '1')
			ft_error(NULL, map, NOTVALID);
		j++;
	}
	i = 1;
	while (i < (map->height - 1))
	{
		if (map->mtrx[i][0] != '1'
			|| map->mtrx[i][map->width - 1] != '1')
			ft_error(NULL, map, NOTVALID);
		i++;
	}
}

void	get_player_coord(t_player *coord, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'P')
			{
				coord->x = j;
				coord->y = i;
			}
		}
	}
}

/* void	check_directions(t_map *map,t_map *stats, size_t y, size_t x)
{
	if (map->path != FALSE)
		return ;
	if (map->mtrx[y][x] == 'C')
		stats->collecs++;
	if (map->mtrx[y][x] == 'E' && stats->collecs == map->collecs)
		map->path++;
	if (ft_strchr("0CE", map->mtrx[y - 1][x]))
		check_directions(map, stats, y - 1, x);
	if (ft_strchr("0CE", map->mtrx[y][x + 1]))
		check_directions(map, stats, y, x + 1);
	if (ft_strchr("0CE", map->mtrx[y + 1][x]))
		check_directions(map, stats, y + 1, x);
	if (ft_strchr("0CE", map->mtrx[y][x - 1]))
		check_directions(map, stats, y, x - 1);
} */

//Ya rellena todos los caminos posibles, ahora toca comprobar que 
//no hay ninguna C ni E en el mapa, asi significara que ha pasado
//por todos los collec y la salida

void	check_directions(t_map *map, t_map stats, int y, int x)
{
	if (y < 0 || y >= (int)map->height
		|| x < 0 || x >= (int)map->width)
		return ;
	if (!ft_strchr("0CEP", map->mtrx[y][x]))
		return ;
	map->mtrx[y][x] = 'X';
	check_directions(map, stats, y - 1, x);
	check_directions(map, stats, y, x + 1);
	check_directions(map, stats, y + 1, x);
	check_directions(map, stats, y, x - 1);
}

static void	check_path(t_map *map)
{
	t_player	coord;
	t_map		stats;

	stats.collecs = 0;
	stats.exits = FALSE;
	stats.mtrx = map->mtrx;
	get_player_coord(&coord, map->mtrx);
	check_directions(map, stats, coord.y, coord.x);
	print_map(map->mtrx);
	/* if (map->path == FALSE)
		ft_error(NULL, map, NOTVALID); */
}

void	check_map(t_map *map)
{
	check_wall(map);
	check_path(map);
}
