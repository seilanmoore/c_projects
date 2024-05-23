/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:49:55 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/23 09:57:43 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	end_game(t_data *data)
{
	data->player.moves++;
	ft_printf("Moves: %d\n", (int)data->player.moves);
	ft_printf(
		"You won in %d moves, congratulations!\n", (int)data->player.moves);
	terminate(data);
}
