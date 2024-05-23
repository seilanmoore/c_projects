/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:43:37 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/23 12:48:03 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	get_player_coord(t_data *data, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'P')
			{
				data->player.coord.x = j;
				data->player.coord.y = i;
			}
		}
	}
}

static char	**ft_mtrxdup(char **mtrx)
{
	char	**dup;
	int		i;

	i = 0;
	dup = NULL;
	while (mtrx[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	if (dup == NULL)
		return (NULL);
	i = -1;
	while (mtrx[++i])
		dup[i] = ft_strdup(mtrx[i]);
	dup[i] = NULL;
	return (dup);
}

static void	check_directions(t_map *map, char ***mtrx, int y, int x)
{
	if (!ft_strchr("0CEP", (*mtrx)[y][x]))
		return ;
	(*mtrx)[y][x] = 'X';
	check_directions(map, mtrx, y - 1, x);
	check_directions(map, mtrx, y, x + 1);
	check_directions(map, mtrx, y + 1, x);
	check_directions(map, mtrx, y, x - 1);
}

static int	check_stats(char **mtrx)
{
	int	i;

	i = -1;
	while (mtrx[++i])
	{
		if (ft_strchr(mtrx[i], 'E') || ft_strchr(mtrx[i], 'C'))
			return (1);
	}
	return (0);
}

void	check_path(t_data *data)
{
	size_t	x;
	size_t	y;
	char	**tmp;

	tmp = ft_mtrxdup(data->map.mtrx);
	if (tmp == NULL)
		ft_error(data, NULL);
	get_player_coord(data, data->map.mtrx);
	x = data->player.coord.x;
	y = data->player.coord.y;
	check_directions(&(data->map), &tmp, y, x);
	if (check_stats(tmp))
	{
		free_map(tmp);
		ft_error(data, NOTVALID);
	}
	free_map(tmp);
}
