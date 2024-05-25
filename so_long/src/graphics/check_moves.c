/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:53:51 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/25 22:20:09 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	check_up(t_data *data, t_coord *coord)
{
	get_player_coord(data, data->map.mtrx);
	if (ft_strchr("CE0", data->map.mtrx[coord->y - 1][coord->x]))
	{
		if (data->map.mtrx[coord->y - 1][coord->x] == 'E'
			&& data->player.collecs == data->map.collecs)
			end_game(data);
		else if (data->map.mtrx[coord->y - 1][coord->x] != 'E')
		{
			if (data->map.mtrx[coord->y - 1][coord->x] == 'C')
				data->player.collecs++;
			draw_player(data, coord->x, coord->y - 1);
			draw_ground(data, coord->x, coord->y);
			data->map.mtrx[coord->y - 1][coord->x] = 'P';
			data->map.mtrx[coord->y][coord->x] = '0';
			data->player.moves++;
			ft_printf("Moves: %d\n", (int)data->player.moves);
		}
	}
}

void	check_right(t_data *data, t_coord *coord)
{
	get_player_coord(data, data->map.mtrx);
	if (ft_strchr("CE0", data->map.mtrx[coord->y][coord->x + 1]))
	{
		if (data->map.mtrx[coord->y][coord->x + 1] == 'E'
			&& data->player.collecs == data->map.collecs)
			end_game(data);
		else if (data->map.mtrx[coord->y][coord->x + 1] != 'E')
		{
			if (data->map.mtrx[coord->y][coord->x + 1] == 'C')
				data->player.collecs++;
			draw_player(data, coord->x + 1, coord->y);
			draw_ground(data, coord->x, coord->y);
			data->map.mtrx[coord->y][coord->x + 1] = 'P';
			data->map.mtrx[coord->y][coord->x] = '0';
			data->player.moves++;
			ft_printf("Moves: %d\n", (int)data->player.moves);
		}
	}
}

void	check_down(t_data *data, t_coord *coord)
{
	get_player_coord(data, data->map.mtrx);
	if (ft_strchr("CE0", data->map.mtrx[coord->y + 1][coord->x]))
	{
		if (data->map.mtrx[coord->y + 1][coord->x] == 'E'
			&& data->player.collecs == data->map.collecs)
			end_game(data);
		else if (data->map.mtrx[coord->y + 1][coord->x] != 'E')
		{
			if (data->map.mtrx[coord->y + 1][coord->x] == 'C')
				data->player.collecs++;
			draw_player(data, coord->x, coord->y + 1);
			draw_ground(data, coord->x, coord->y);
			data->map.mtrx[coord->y + 1][coord->x] = 'P';
			data->map.mtrx[coord->y][coord->x] = '0';
			data->player.moves++;
			ft_printf("Moves: %d\n", (int)data->player.moves);
		}
	}
}

void	check_left(t_data *data, t_coord *coord)
{
	get_player_coord(data, data->map.mtrx);
	if (ft_strchr("CE0", data->map.mtrx[coord->y][coord->x - 1]))
	{
		if (data->map.mtrx[coord->y][coord->x - 1] == 'E'
			&& data->player.collecs == data->map.collecs)
			end_game(data);
		else if (data->map.mtrx[coord->y][coord->x - 1] != 'E')
		{
			if (data->map.mtrx[coord->y][coord->x - 1] == 'C')
				data->player.collecs++;
			draw_player(data, coord->x - 1, coord->y);
			draw_ground(data, coord->x, coord->y);
			data->map.mtrx[coord->y][coord->x - 1] = 'P';
			data->map.mtrx[coord->y][coord->x] = '0';
			data->player.moves++;
			ft_printf("Moves: %d\n", (int)data->player.moves);
		}
	}
}
