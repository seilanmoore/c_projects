/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:16:11 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/10 12:21:08 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*one_philo(void *philo_)
{
	t_philo	*philo;

	philo = (t_philo *)philo_;
	sync_threads(philo->data);
	set_long(&(philo->philo_mutex), &(philo->last_meal), \
	get_time());
	increase_running_threads(&(philo->philo_mutex), \
	&(philo->data->n_threads_running));
	logs(philo, FORK);
	while (!simulation_ended(philo->data))
		usleep(200);
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->first_fork->fork));
	logs(philo, FORK);
	pthread_mutex_lock(&(philo->second_fork->fork));
	logs(philo, FORK);
	set_long(&(philo->philo_mutex), &(philo->last_meal), get_time());
	philo->n_meal++;
	logs(philo, EAT);
	ft_usleep(philo->data->info.eat_t, philo->data);
	if (philo->data->info.n_meal > 0 && \
	philo->n_meal == philo->data->info.n_meal)
		set_bool(&(philo->philo_mutex), &(philo->full), true);
	pthread_mutex_unlock(&(philo->first_fork->fork));
	pthread_mutex_unlock(&(philo->second_fork->fork));
}

void	*simulation(void *philo_)
{
	t_philo	*philo;

	philo = (t_philo *)philo_;
	sync_threads(philo->data);
	set_long(&(philo->philo_mutex), &(philo->last_meal), get_time());
	increase_running_threads(&(philo->data->data_mutex), \
	&(philo->data->n_threads_running));
	if (philo->id % 2)
		ft_usleep(60, philo->data);
	while (!simulation_ended(philo->data))
	{
		if (get_bool(&(philo->data->data_mutex), &(philo->full)))
			break ;
		eat(philo);
		logs(philo, SLEEP);
		ft_usleep(philo->data->info.sleep_t, philo->data);
		logs(philo, THINK);
	}
	return (0);
}

static int	init_threads(t_data *data)
{
	int			i;
	int			j;

	i = -1;
	while (++i < data->info.n_philo)
	{
		if (pthread_create(&(data->philo[i].thread), \
		NULL, &simulation, &(data->philo[i])))
		{
			j = -1;
			while (++j < i)
				pthread_join(data->philo[i].thread, NULL);
			return (data->e_code = E_THREAD_CREATE);
		}
	}
	return (0);
}

void	start_simulation(t_data *data)
{
	if (data->info.n_meal == 0)
		return ;
	if (data->info.n_philo == 1)
	{
		if (pthread_create(&(data->philo[0].thread), \
		NULL, one_philo, (void *)&(data->philo[0])))
		{
			pthread_join(data->philo[0].thread, NULL);
			data->e_code = E_THREAD_CREATE;
			return ;
		}
	}
	else
	{
		if (init_threads(data))
			return ;
	}
	pthread_create(&(data->monitor), NULL, monitor, (void *)data);
	data->start_time = get_time();
	set_bool(&(data->data_mutex), &(data->threads_ready), true);
}
