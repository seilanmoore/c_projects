/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:55:28 by smoore-a          #+#    #+#             */
/*   Updated: 2024/03/05 20:43:07 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_mtrx	*init_map(int argc)
{
	t_mtrx	*map;
	int		i;

	i = -1;
	map = (t_mtrx*)malloc((argc + 1) * sizeof(t_mtrx));
	if (!map)
		ft_error(NULL, NULL, NULL);
	while (++i < argc)
		map[i] = (t_mtrx){NULL, 0, 0, 0, 0, 0};
	map[i] = (t_mtrx){NULL, 0, 0, 0, 0, 0};
	return (map);
}

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

int	count_lines(t_mtrx **maps, char *argv)
{
	int		n_lines;
	int		fd;
	char	*line;

	n_lines = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (free_map(*maps), ft_error(NULL, NULL, NULL), -1);
	line = get_next_line(fd);
	while(line)
	{
		n_lines++;
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
		return (free_map(*maps), ft_error(NULL, NULL, NULL), -1);
	if (!n_lines)
		return(free_map(*maps), ft_error(NULL, "empty file:", argv), -1);
	return (n_lines);
}

int	free_map(t_mtrx *maps)
{
	int	i;
	int	line;

	i = 0;
	if (!maps)
		return (0);
	while (maps[i].map)
	{
		line = 0;
		while (maps[i].map[line])
		{
			free(maps[i].map[line]);
			maps[i].map[line] = NULL;
			line++;
		}
		free(maps[i].map);
		maps[i].map = NULL;
		i++;
	}
	free(maps);
	maps = (t_mtrx *)NULL;
	return (0);
}

void	assign_lines(t_mtrx **maps, t_mtrx *map, char *argv, int fd)
{
	int	i;

	i = -1;
	while (++i < map->row)
	{
		map->map[i] = get_next_line(fd);
		if (map->map[i] == NULL)
		{
			close(fd);
			free_map(*maps);
			ft_error(NULL, NULL, argv);
		}
	}
	map->map[i] = NULL;
}

t_mtrx	allocate_lines(t_mtrx **maps, char *argv, int f_pos)
{
	t_mtrx	map;
	int	fd;

	map = (*maps)[f_pos];
	map.row = count_lines(maps, argv);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		free_map(*maps);
		ft_error(NULL, NULL, argv);
	}
	map.map = (char **)malloc((map.row + 1) * sizeof(char*));
	if (!map.map)
	{
		free_map(*maps);
		ft_error(NULL, NULL, argv);
	}
	assign_lines(maps, &map, argv, fd);
	if (close(fd) == -1)
	{
		free_map(*maps);
		ft_error(NULL, NULL, argv);
	}
	return (map);
}

int	handle_lines(t_mtrx **maps, char *argv, int f_pos)
{
	(*maps)[f_pos] = allocate_lines(maps, argv, f_pos);
	if ((*maps)[f_pos].map == NULL)
		return (free_map(*maps), ft_error(NULL, NULL, NULL), -1);
	return (0);
}

void	print_maps(t_mtrx *maps, int argc, char **argv)
{
	int	i;
	int	line;

	i = -1;
	while (++i < argc)
	{
		ft_printf("FILE: %s\n\n", argv[i]);
		line = 0;
		while (maps[i].map[line])
		{
			ft_printf("%s\n", maps[i].map[line]);
			line++;
		}
	}
}

int	handle_files(int argc, char **argv)
{
	t_mtrx	*maps;
	int		i;

	maps = init_map(argc);
	i = -1;
	while (++i < argc)
	{
		handle_lines(&maps, argv[i], i);
	}
	print_maps(maps, argc, argv);
	free_map(maps);
	return (0);
}

/* void	create_mtrx(char **arg)
{
	
} */