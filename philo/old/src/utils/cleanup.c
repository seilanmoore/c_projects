/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:55:19 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/25 11:11:16 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	ft_clear(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_join(data->tid[i], NULL);
	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&(data->fork[i]));
		pthread_mutex_destroy(&(data->philo[i].lock));
	}
	pthread_mutex_destroy(&(data->write));
	pthread_mutex_destroy(&(data->lock));
	free(data->tid);
	free(data->fork);
	free(data->philo);
}

void	clear_one(t_data *data)
{
	pthread_mutex_destroy(&(data->fork[0]));
	pthread_mutex_destroy(&(data->philo[0].lock));
	pthread_mutex_destroy(&(data->write));
	pthread_mutex_destroy(&(data->lock));
	free(data->tid);
	free(data->fork);
	free(data->philo);
}
