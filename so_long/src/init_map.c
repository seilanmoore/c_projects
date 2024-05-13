/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:47:41 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/13 19:29:47 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_map(t_map *map, char *fn)
{
	map->fn = fn;
	map->fd = NONE;
	map->mtrx = NULL;
	map->width = NONE;
	map->height = NONE;
	map->collecs = NONE;
	map->exits = NONE;
	map->starts = NONE;
	map->walls = NONE;
	map->spaces = NONE;
}

void	init_mtrx(t_map *map)
{
	map->mtrx = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->mtrx)
		map_error(map, NULL);
}
