/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:55:19 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/18 09:43:39 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	ft_clear(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&(data->fork[i]));
		pthread_mutex_destroy(&(data->philo[i].lock));
	}
	pthread_mutex_destroy(&(data->write));
	pthread_mutex_destroy(&(data->lock));
	if (data->tid)
		free(data->tid);
	if (data->fork)
		free(data->fork);
	if (data->philo)
		free(data->philo);
}
