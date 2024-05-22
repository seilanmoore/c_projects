/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:33:13 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/22 19:43:12 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	clean_gnl(t_data *data, char **line)
{
	while (*line)
	{
		free(*line);
		*line = get_next_line(data->map.fd);
	}
	*line = NULL;
	ft_error(data, NOTVALID);
}

static void	map_size(t_data *data)
{
	char	*line;

	openf(data);
	line = get_next_line(data->map.fd);
	if (!line)
		ft_error(data, "Empty file");
	if (ft_strchr(line, '\n') == NULL)
		ft_error(data, NOTVALID);
	data->map.width = ft_strchr(line, '\n') - line;
	while (line)
	{
		if ((ft_strchr(line, '\n') && ft_strlen(line) != data->map.width + 1) \
		|| (!ft_strchr(line, '\n') && ft_strlen(line) != data->map.width) \
		|| check_sections(&(data->map), line) == ERROR)
			clean_gnl(data, &line);
		data->map.height++;
		free(line);
		line = get_next_line(data->map.fd);
	}
	if (data->map.player != TRUE || data->map.exits != TRUE
		|| data->map.collecs == FALSE || data->map.walls == FALSE
		|| data->map.spaces == FALSE)
		ft_error(data, NOTVALID);
	closef(data);
}

static void	init_mtrx(t_data *data)
{
	data->map.mtrx = ft_calloc(data->map.height + 1, sizeof(char *));
	if (!data->map.mtrx)
		ft_error(data, NULL);
}

static void	assign_lines(t_data *data)
{
	char	*line;
	size_t	i;

	i = 0;
	while (i < data->map.height)
	{
		line = get_next_line(data->map.fd);
		data->map.mtrx[i] = ft_substr(line, 0, data->map.width);
		free(line);
		if (data->map.mtrx[i] == NULL)
			ft_error(data, NULL);
		i++;
	}
	data->map.mtrx[i] = NULL;
}

void	parse_file(t_data *data, int argc, char **argv)
{
	char	*fn_ext;

	argc--;
	if (!argc)
		ft_error(data, "No arguments");
	argv++;
	data->map.fn = *argv;
	fn_ext = ft_strnstr(*argv, ".ber", ft_strlen(*argv));
	if (!fn_ext || ft_strlen(fn_ext) != 4 || **argv == '.')
		ft_error(data, "Not valid filename");
	map_size(data);
	init_mtrx(data);
	openf(data);
	assign_lines(data);
	closef(data);
}
