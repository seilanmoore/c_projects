/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:53:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/13 19:11:06 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_sections(t_map *map, char *line)
{
	while (*line != '\n')
	{
		if (*line == 'C')
			map->collecs++;
		else if (*line == 'E')
			map->exits++;
		else if (*line == 'P')
			map->starts++;
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

/* void	check_map(char **map)
{

} */
