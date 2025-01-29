/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:09:30 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/29 21:45:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	cleanup(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&(data->data_mutex));
	pthread_mutex_destroy(&(data->print_mutex));
	i = -1;
	while (++i < data->info.n_philo)
	{
		pthread_mutex_destroy(&(data->fork[i].fork));
		pthread_mutex_destroy(&(data->philo[i].philo_mutex));
	}
	free(data->philo);
	free(data->fork);
}
