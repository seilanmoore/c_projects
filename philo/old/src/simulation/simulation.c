/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:05:16 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/25 10:04:20 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) data_pointer;
	pthread_mutex_lock(&(philo->data->write));
	printf("data val: %d", philo->data->dead);
	pthread_mutex_unlock(&(philo->data->write));
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&(philo->lock));
		if (philo->data->finished >= philo->data->philo_num)
			philo->data->dead = 1;
		pthread_mutex_unlock(&(philo->lock));
	}
	return ((void *)0);
}

static void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (philo->data->dead == FALSE)
	{
		pthread_mutex_lock(&(philo->lock));
		if (get_time() >= philo->time_to_die && philo->eating == FALSE)
			logs(DIED, philo);
		if (philo->eat_count == philo->data->must_eat)
		{
			pthread_mutex_lock(&(philo->data->lock));
			philo->data->finished++;
			philo->eat_count++;
			pthread_mutex_unlock(&(philo->data->lock));
		}
		pthread_mutex_unlock(&(philo->lock));
	}
	return ((void *)SUCCESS);
}

static void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	pthread_mutex_lock(&(philo->data->lock));
	philo->time_to_die = get_time() + philo->data->death_time;
	pthread_mutex_unlock(&(philo->data->lock));
	if (pthread_create(&(philo->t1), NULL, &supervisor, (void *)philo))
		return ((void *)ERROR);
	pthread_mutex_lock(&(philo->data->lock));
	while (philo->data->dead == FALSE)
	{
		pthread_mutex_unlock(&(philo->data->lock));
		eat(philo);
		logs(THINKING, philo);
		pthread_mutex_lock(&(philo->data->lock));
	}
	pthread_mutex_unlock(&(philo->data->lock));
	pthread_join(philo->t1, NULL);
	return ((void *)SUCCESS);
}

int	simulation(t_data *data)
{
	int			i;
	pthread_t	t0;

	i = -1;
	data->start_time = get_time();
	if (data->must_eat > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &(data->philo[0])))
			return (ft_error(data, PHILO ECREATE, "t0"));
	}
	while (++i < data->philo_num)
	{
		if (pthread_create(&(data->tid[i]), NULL, &routine, &(data->philo[i])))
			return (ft_error(data, PHILO ECREATE, "tid[i]"));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->philo_num)
		pthread_join(data->tid[i], NULL);
	return (SUCCESS);
}
