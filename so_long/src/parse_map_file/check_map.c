/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:53:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/22 12:59:10 by smoore-a         ###   ########.fr       */
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

static void	check_wall(t_data *data)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < data->map.width)
	{
		if (data->map.mtrx[0][j] != '1'
			|| data->map.mtrx[data->map.height - 1][j] != '1')
			ft_error(data, NOTVALID);
		j++;
	}
	i = 1;
	while (i < (data->map.height - 1))
	{
		if (data->map.mtrx[i][0] != '1'
			|| data->map.mtrx[i][data->map.width - 1] != '1')
			ft_error(data, NOTVALID);
		i++;
	}
}

void	check_map(t_data *data)
{
	check_wall(data);
	check_path(data);
}
