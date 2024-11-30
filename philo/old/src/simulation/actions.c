/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:22:27 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/25 12:50:38 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(10);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&(philo->lock));
	if (philo->data->dead == FALSE)
		logs(TAKE_FORK, philo);
	pthread_mutex_unlock(&(philo->lock));
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&(philo->lock));
	if (philo->data->dead == FALSE)
		logs(TAKE_FORK, philo);
	else
		pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&(philo->lock));
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	logs(SLEEPING, philo);
	ft_usleep(philo->data->sleep_time);
}

void	logs(char *log, t_philo *philo)
{
	time_t	time;

	time = get_time() - philo->data->start_time;
	if (ft_strcmp(DIED, log) == 0 && philo->data->dead == FALSE)
	{
		pthread_mutex_lock(&(philo->data->write));
		printf("%ld\t%d %s\n", time, philo->id, log);
		pthread_mutex_unlock(&(philo->data->write));
		pthread_mutex_lock(&(philo->data->lock));
		philo->data->dead = 1;
		pthread_mutex_unlock(&(philo->data->lock));
		/* if (philo->data->philo_num > 1)
			pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork); */
	}
	if (philo->data->dead == FALSE)
	{
		pthread_mutex_lock(&(philo->data->write));
		printf("%ld\t%d %s\n", time, philo->id, log);
		pthread_mutex_unlock(&(philo->data->write));
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	if (philo->data->dead == FALSE)
	{
		pthread_mutex_lock(&(philo->lock));
		philo->eating = 1;
		philo->time_to_die = get_time() + philo->data->death_time;
		logs(EATING, philo);
		philo->eat_count++;
		ft_usleep(philo->data->eat_time);
		philo->eating = 0;
		pthread_mutex_unlock(&(philo->lock));
		drop_forks(philo);
	}
}
