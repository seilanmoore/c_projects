/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:53:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 12:39:23 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

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

void	check_map(t_map *map)
{
	check_wall(map);
	check_path(map);
}
