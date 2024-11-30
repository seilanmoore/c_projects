/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:50:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/30 12:50:07 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor(void *philo_)
{
	t_philo *philo;
	time_t	time;

	philo = philo_;
	pthread_mutex_lock(&(philo->data->state_m.lock));
	while (philo->data->dead == FALSE)
	{
		time = get_time() - philo->last_meal;
		pthread_mutex_unlock(&(philo->data->state_m.lock));
		if (time >= philo->data->info.die_t)
		{
			logs(philo, DIE, time);
			pthread_mutex_lock(&(philo->data->state_m.lock));
			philo->data->dead = TRUE;
			pthread_mutex_unlock(&(philo->data->state_m.lock));
		}
		pthread_mutex_lock(&(philo->data->state_m.lock));
	}
	pthread_mutex_unlock(&(philo->data->state_m.lock));
	return (0);
}

void	*routine(void *philo_)
{
	t_philo		*philo;
	pthread_t	monitor_t;

	philo = (t_philo*)philo_;
	if (pthread_create(&monitor_t, NULL, &monitor, philo))
	{
		pthread_mutex_lock(&(philo->data->err_code_m.lock));
		philo->data->e_code = E_THREAD_CREATE;
		pthread_mutex_unlock(&(philo->data->err_code_m.lock));
		return (0);
	}
	while (1)
	{
		take_fork(philo);
		pthread_mutex_lock(&(philo->data->state_m.lock));
		if (philo->data->dead == TRUE)
		{
			pthread_mutex_unlock(&(philo->data->state_m.lock));
			break ;
		}
		pthread_mutex_unlock(&(philo->data->state_m.lock));
	}
	pthread_join(monitor_t, NULL);
	return (0);
}
