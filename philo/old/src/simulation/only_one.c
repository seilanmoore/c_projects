/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:00:32 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/25 12:46:28 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	*one_supervisor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (philo->data->dead == FALSE)
	{
		if (get_time() >= philo->time_to_die)
		{
			pthread_mutex_unlock(philo->r_fork);
			logs(DIED, philo);
		}
	}
	return ((void *)SUCCESS);
}

static void	*one_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	eat(philo);
	return ((void *)SUCCESS);
}

int	case_one(t_data *data)
{
	pthread_t	thread[2];

	data->start_time = get_time();
	data->philo[0].time_to_die = get_time() + data->death_time;
	if (pthread_create(&(thread[0]), NULL, &one_routine, &(data->philo[0])))
		return (clear_one(data), EXIT_FAILURE);
	if (pthread_create(&(thread[1]), NULL, &one_supervisor, &(data->philo[0])))
		return (clear_one(data), EXIT_FAILURE);
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
/* 	while (1)
	{
		pthread_mutex_lock(&(data->lock));
		if (data->dead == TRUE)
		{
			pthread_mutex_unlock(&(data->lock));
			break ;
		}
		pthread_mutex_unlock(&(data->lock));
		ft_usleep (0);
	} */
	clear_one(data);
	return (SUCCESS);
}
