/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:09:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/30 11:40:12 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	cleanup(t_data *data)
{
	int	i;

	if (data->print_m.to_destroy)
		pthread_mutex_destroy(&(data->print_m.lock));
	if (data->die_t_m.to_destroy)
		pthread_mutex_destroy(&(data->die_t_m.lock));
	if (data->n_meal_m.to_destroy)
		pthread_mutex_destroy(&(data->n_meal_m.lock));
	if (data->state_m.to_destroy)
		pthread_mutex_destroy(&(data->state_m.lock));
	if (data->err_code_m.to_destroy)
		pthread_mutex_destroy(&(data->err_code_m.lock));
	i = -1;
	while (++i < data->info.n_philo)
	{
		if (data->fork[i].to_destroy)
			pthread_mutex_destroy(&(data->fork[i].lock));
	}
	free(data->philo);
	free(data->fork);
}
