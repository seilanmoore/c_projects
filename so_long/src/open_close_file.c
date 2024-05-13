/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:07:43 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/13 13:07:54 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	openf(t_map *map)
{
	map->fd = open(map->fn, O_RDONLY);
	if (map->fd == ERROR)
		map_error(map, NULL);
}

void	closef(t_map *map)
{
	close(map->fd);
	if (map->fd == ERROR)
		map_error(map, NULL);
}
