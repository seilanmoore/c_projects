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

#include "../include/fdf.h"

void	free_columns(char **map)
{
	int	column;

	column = 0;
	while (map[column])
	{
		free(map[column]);
		map[column] = NULL;
		column++;
	}
}

void	free_rows(char ***map)
{
	int	row;

	row = 0;
	while (map[row])
	{
		free_columns(map[row]);
		free(map[row]);
		map[row] = NULL;
		row++;
	}
}

void	free_map(t_mtrx *maps)
{
	int	i;

	i = 0;
	while (maps[i].map)
	{
		free_rows(maps[i].map);
		free(maps[i].map);
		maps[i].map = NULL;
		i++;
	}
}

void	free_mtrx(t_mtrx *maps)
{
	if (!maps)
		return ;
	free_map(maps);
	free(maps);
	maps = (t_mtrx *)NULL;
}

void	map_error(t_mtrx *maps, char *message, char *file)
{
	if (message && !file)
		ft_printf("ERROR: %s\n", message);
	else if (message && file)
		ft_printf("ERROR: %s -- FILE: %s\n", message, file);
	else if (file && !message)
		ft_printf("ERROR: %s -- FILE: %s\n", strerror(errno), file);
	else
		ft_printf("ERROR: %s\n", strerror(errno));
	free_mtrx(maps);
	exit(EXIT_FAILURE);
}

t_mtrx	*init_map(int argc)
{
	t_mtrx	*map;
	int		i;

	i = -1;
	map = (t_mtrx*)malloc((argc + 1) * sizeof(t_mtrx));
	if (!map)
		map_error(NULL, NULL, NULL);
	while (++i < argc)
		map[i] = (t_mtrx){NULL, NULL, NULL, 0, 0};
	map[i] = (t_mtrx){NULL, NULL, NULL, 0, 0};
	return (map);
}

/* void	init_point(t_mtrx *map)
{
	int		i;

	i = -1;
	map = (t_mtrx*)malloc((argc + 1) * sizeof(t_mtrx));
	if (!map)
		ft_error(NULL, NULL, NULL);
	while (++i < argc)
		map[i] = (t_mtrx){NULL, NULL, 0, 0};
	map[i] = (t_mtrx){NULL, NULL, 0, 0};
	return (map);
} */

void	handle_args(int	argc, char **argv)
{
	char	*fdf_file;
	int		i;
	
	argc--;
	if (!argc)
		ft_error(NULL, "No arguments", NULL);
	argv++;
	i = -1;
	while(++i < argc)
	{
		fdf_file = ft_strnstr(argv[i], ".fdf", ft_strlen(argv[i]));
		if (!fdf_file || !ft_strncmp(argv[i], 
			".fdf", ft_strlen(argv[i])) || *(fdf_file + 4))
			ft_error(NULL, "Invalid .fdf filename", argv[i]);
	}
	handle_files(argc, argv);
}

void	clean_gnl(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	count_lines(t_mtrx *maps, t_mtrx map)
{
	int		n_lines;
	int		fd;
	char	*line;

	n_lines = 0;
	fd = open(map.file, O_RDONLY);
	if (fd == -1)
		return (map_error(maps, NULL, map.file), -1);
	line = get_next_line(fd);
	while(line)
	{
		n_lines++;
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
		return (map_error(maps, NULL, map.file), -1);
	if (!n_lines)
		return(map_error(maps, "empty file", map.file), -1);
	return (n_lines);
}

int	count_columns(t_mtrx *maps, t_mtrx map)
{
	int	i;
	int	j;

	i = 0;
	while(i < map.row)
	{
		j = 0;
		while (map.map[i][j] && map.map[i][j][0] != '\n')
			j++;
		if (!i)
			map.col = j;
		if (j != map.col)
			map_error(maps, "Not all column lengths are the same",
				map.file);
		i++;
	}
	return (j);
}

void	assign_lines(t_mtrx *maps, t_mtrx map, int fd)
{
	char	*line;
	int		i;

	i = -1;
	while (++i < map.row)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			map_error(maps, NULL, map.file);
		}
		map.map[i] = ft_split(line, ' ');
		if (!map.map[i])
		{
			clean_gnl(line, fd);
			close(fd);
			map_error(maps, NULL, map.file);
		}
		free(line);
	}
	map.map[i] = NULL;
}

void	allocate_lines(t_mtrx *maps, int f_pos)
{
	int	fd;

	maps[f_pos].row = count_lines(maps, maps[f_pos]);
	fd = open(maps[f_pos].file, O_RDONLY);
	if (fd == -1)
		map_error(maps, NULL, maps[f_pos].file);
	maps[f_pos].map = (char ***)calloc((maps[f_pos].row + 1), sizeof(char**));
	if (!maps[f_pos].map)
		map_error(maps, NULL, maps[f_pos].file);
	assign_lines(maps, maps[f_pos], fd);
	if (close(fd) == -1)
		map_error(maps, NULL, maps[f_pos].file);
	maps[f_pos].col = count_columns(maps, maps[f_pos]);
}

void	print_maps(t_mtrx *maps, int argc, char **argv)
{
	int	i;
	int	line;
	int	column;

	i = -1;
	while (++i < argc)
	{
		ft_printf("FILE: %s\n\n", argv[i]);
		line = 0;
		while (maps[i].map[line])
		{
			column = 0;
			while (maps[i].map[line][column])
			{
				ft_printf("%s", maps[i].map[line][column++]);
				if (maps[i].map[line][column])
					ft_printf(" ");
			}
			ft_printf("\n");
			line++;
		}
	}
}

void	handle_files(int argc, char **argv)
{
	t_mtrx	*maps;
	int		i;

	maps = init_map(argc);
	i = -1;
	while (++i < argc)
	{
		maps[i].file = argv[i];
		allocate_lines(maps, i);
	}
	//print_maps(maps, argc, argv);
	free_mtrx(maps);
}
