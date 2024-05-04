/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:55:28 by smoore-a          #+#    #+#             */
/*   Updated: 2024/03/11 12:19:41 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	ft_printf("\n");
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			ft_printf(" %c ", map[i][j]);
		ft_printf("\n");
	}
}

void	free_map(char ***map)
{
	int	i;

	if (*map == NULL)
		return ;
	i = 0;
	while ((*map)[i])
	{
		free((*map)[i]);
		i++;
	}
	free(*map);
	*map = NULL;
}

void	map_error(char ***map, char *message, char *file, int fd)
{
	if (message && !file)
		ft_printf("ERROR: %s\n", message);
	else if (message && file)
		ft_printf("ERROR: %s -- FILE: %s\n", message, file);
	else if (file && !message)
		ft_printf("ERROR: %s -- FILE: %s\n", strerror(errno), file);
	else
		ft_printf("ERROR: %s\n", strerror(errno));
	free_map(map);
	if (fd > 0)
		close(fd);
	exit(EXIT_FAILURE);
}

void	assign_lines(char ***map, char *file, int fd, int row)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (row-- > 0)
	{
		line = get_next_line(fd);
		if (line == NULL)
			map_error(map, "gnl error", file, FALSE);
		j = -1;
		while (line[++j] && line[j] != '\n')
			(*map)[i][j] = line[j];
		i++;
		free(line);
	}
	(*map)[i] = NULL;
}

void	init_map(char ***map, int row, int col)
{
	int	i;

	*map = (char **)malloc((row + 1) * sizeof(char *));
	if (!(*map))
		map_error(NULL, NULL, NULL, FALSE);
	i = 0;
	while (row-- > 0)
		(*map)[i++] = ft_calloc(col + 1, sizeof(char));
	(*map)[i] = NULL;
}

void	clean_gnl(char **line, int fd)
{
	while (*line)
	{
		free(*line);
		*line = get_next_line(fd);
	}
	*line = NULL;
}

int	count_columns(char *line)
{
	int	i;

	if (!line)
		return (ERROR);
	i = 0;
	while(line[i] && line[i] != '\n')
	{
		if (line [i] != '0' && line[i] != '1' && line[i] != 'C'
			&& line[i] != 'E' && line[i] != 'P')
			return (ERROR);
		i++;
	}
	return (i);
}

void	count_lines(char ***map, char *file, int *row, int *col)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		map_error(map, NULL, file, FALSE);
	line = get_next_line(fd);
	if (!line)
		map_error(map, "empty file", file, FALSE);
	*col = count_columns(line);
	while(line)
	{
		if (*col != count_columns(line) || count_columns(line) == ERROR)
		{
			clean_gnl(&line, fd);
			map_error(map, "invalid map", file, fd);
		}
		*row = *row + 1;
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) == ERROR)
		map_error(map, NULL, file, FALSE);
}

void	allocate_lines(char ***map, char *file)
{
	int		row;
	int		col;
	int		fd;

	row = 0;
	col = 0;
	count_lines(map, file, &row, &col);
	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		map_error(map, NULL, file, FALSE);
	init_map(map, row, col);
	if (!map)
		map_error(map, NULL, file, fd);
	assign_lines(map, file, fd, row);
	if (close(fd) == ERROR)
		map_error(map, NULL, file, FALSE);
}

char	**handle_file(char *file)
{
	char	**map;

	map = NULL;
	allocate_lines(&map, file);
	return (map);
}

char	**handle_args(int	argc, char **argv)
{
	char	*file_ext;

	argc--;
	if (!argc)
          ft_error(NULL, "No arguments", NULL);
        argv++;
	file_ext = ft_strnstr(*argv, ".ber", ft_strlen(*argv));
	if (!file_ext || ft_strlen(file_ext) != 4 || **argv == '.')
		ft_error(NULL, "Invalid .ber filename", *argv);
	return (handle_file(*argv));
}
