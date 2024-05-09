/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:55:28 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/06 13:15:20 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	**print_map(char **map)
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
	return (map);
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
	if (map)
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

void	clean_gnl(char **line, int fd, char *file)
{
	while (*line)
	{
		free(*line);
		*line = get_next_line(fd);
	}
	*line = NULL;
	map_error(NULL, "invalid map", file, fd);
}

int	count_columns(char *line)
{
	int	i;

	i = 0;
	while(line[i] && line[i] != '\n')
		i++;
	return (i);
}

void	openf(int *fd, char *file)
{
	*fd = open(file, O_RDONLY);
	if (*fd == ERROR)
		map_error(NULL, NULL, file, FALSE);
}

void	closef(int fd, char *file)
{
	close(fd);
	if (fd == ERROR)
		map_error(NULL, NULL, file, FALSE);
}

char	*get_line(int fd, char *file)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		map_error(NULL, "empty file", file, FALSE);
	return (line);
}

void	init_parts(t_components *parts)
{
	parts->collec = FALSE;
	parts->exit = FALSE;
	parts->start = FALSE;
}

int	check_parts(t_components *parts, char *line)
{
	int	i;

	i = -1;
	if (!line && (parts->collec == FALSE || parts->exit != TRUE
		|| parts->start != TRUE))
		return (ERROR);
	if (line)
	{
		while (line[++i] && line[i] != '\n')
		{
			if (line[i] == 'C')
				parts->collec++;
			else if (line[i] == 'E')
				parts->exit++;
			else if (line[i] == 'P')
				parts->start++;
			else if (line[i] != '0' && line[i] != '1')
				return (ERROR);
		}
	}
	return (SUCCESS);
}

void	count_lines(char *file, int *row, int *col)
{
	int				fd;
	char			*line;
	t_components	parts;

	openf(&fd, file);
	line = get_line(fd, file);	
	*col = count_columns(line);
	init_parts(&parts);
	while(line)
	{
		if (*col != count_columns(line) || count_columns(line) == ERROR
			|| check_parts(&parts, line) == ERROR)
			clean_gnl(&line, fd, file);
		*row = *row + 1;
		free(line);
		line = get_next_line(fd);
	}
	if (check_parts(&parts, line) == ERROR)
		map_error(NULL, "invalid map", file, fd);
	closef(fd, file);
}

void	allocate_lines(char ***map, char *file)
{
	int		row;
	int		col;
	int		fd;

	row = 0;
	col = 0;
	count_lines(file, &row, &col);
	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		map_error(NULL, NULL, file, FALSE);
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
