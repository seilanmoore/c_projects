/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:55:28 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/17 18:54:17 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	clean_gnl(t_map *map, char **line)
{
	while (*line)
	{
		free(*line);
		*line = get_next_line(map->fd);
	}
	*line = NULL;
	ft_error(NULL, map, NOTVALID);
}

static void	assign_lines(t_map *map)
{
	char	*line;
	size_t	i;

	i = 0;
	while (i < map->height)
	{
		line = get_next_line(map->fd);
		map->mtrx[i] = ft_substr(line, 0, map->width);
		free(line);
		if (map->mtrx[i] == NULL)
			ft_error(NULL, map, NULL);
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
		ft_error(NULL, map, "empty file");
	if (ft_strchr(line, '\n') == NULL)
		ft_error(NULL, map, NOTVALID);
	map->width = ft_strchr(line, '\n') - line;
	while (line)
	{
		if ((ft_strchr(line, '\n') && ft_strlen(line) != map->width + 1) \
		|| (!ft_strchr(line, '\n') && ft_strlen(line) != map->width) \
		|| check_sections(map, line) == ERROR)
			clean_gnl(map, &line);
		map->height++;
		free(line);
		line = get_next_line(map->fd);
	}
	if (map->player != TRUE || map->exits != TRUE
		|| map->collecs == FALSE || map->walls == FALSE
		|| map->spaces == FALSE)
		ft_error(NULL, map, NOTVALID);
	closef(map);
}

void	print_map(char **map)
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

void	parse_file(t_map *map, int argc, char **argv)
{
	char	*fn_ext;

	argc--;
	if (!argc)
		ft_error(NULL, NULL, "No arguments");
	argv++;
	init_map(map, *argv);
	fn_ext = ft_strnstr(*argv, ".ber", ft_strlen(*argv));
	if (!fn_ext || ft_strlen(fn_ext) != 4 || **argv == '.')
		ft_error(NULL, map, "Invalid .ber fnname");
	map_size(map);
	init_mtrx(map);
	openf(map);
	assign_lines(map);
	closef(map);
	print_map(map->mtrx);
}
