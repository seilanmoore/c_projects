/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:55:28 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/13 20:00:13 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	print_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			ft_printf("%c", map[i][j]);
		ft_printf("\n");
	}
}

static void	clean_gnl(t_map *map, char **line)
{
	while (*line)
	{
		free(*line);
		*line = get_next_line(map->fd);
	}
	*line = NULL;
	map_error(map, INVALID);
}

static void	assign_lines(t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	while (map->height-- > 0)
	{
		line = get_next_line(map->fd);
		map->mtrx[i] = ft_substr(line, 0, map->width);
		free(line);
		if (map->mtrx[i] == NULL)
			map_error(map, NULL);
		i++;
	}
	map->mtrx[i] = NULL;
}

static void	map_size(t_map *map)
{
	char	*line;

	openf(map);
	line = get_next_line(map->fd);
	if (!line)
		map_error(map, "empty file");
	map->width = ft_strlen(line);
	while (line)
	{
		if (ft_strlen(line) != map->width
			|| check_sections(map, line) == ERROR)
			clean_gnl(map, &line);
		map->height++;
		free(line);
		line = get_next_line(map->fd);
	}
	if (map->starts != TRUE || map->exits != TRUE
		|| map->collecs == FALSE || map->walls == FALSE
		|| map->spaces == FALSE)
		map_error(map, INVALID);
	closef(map);
	map->width--;
}

void	handle_args(t_map *map, int argc, char **argv)
{
	char	*fn_ext;

	argc--;
	if (!argc)
		ft_error(NULL, "No arguments", NULL);
	argv++;
	fn_ext = ft_strnstr(*argv, ".ber", ft_strlen(*argv));
	if (!fn_ext || ft_strlen(fn_ext) != 4 || **argv == '.')
		ft_error(NULL, "Invalid .ber fnname", *argv);
	init_map(map, *argv);
	map_size(map);
	init_mtrx(map);
	openf(map);
	assign_lines(map);
	closef(map);
	print_map(map->mtrx);
}
