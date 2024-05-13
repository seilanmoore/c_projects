/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:05:31 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/13 18:37:11 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_map(char **map)
{
	int	i;

	if (map == NULL)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	map_error(t_map *map, char *message)
{
	if (message && !map->fn)
		ft_printf("ERROR: %s\n", message);
	else if (message && map->fn)
		ft_printf("ERROR: %s -- FILE: %s\n", message, map->fn);
	else if (map->fn && !message)
		ft_printf("ERROR: %s -- FILE: %s\n", strerror(errno), map->fn);
	else
		ft_printf("ERROR: %s\n", strerror(errno));
	if (map->mtrx)
		free_map(map->mtrx);
	if (map->fd != NONE)
		close(map->fd);
	exit(EXIT_FAILURE);
}
