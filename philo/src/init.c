/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:05:47 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/09 20:31:17 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

/* static int	init_locks(t_data *data)
{
	if (pthread_mutex_init(&(data->print_m.lock), NULL))
		return (data->e_code = E_MUTEX_INIT);
	data->print_m.to_destroy = 1;
	if (pthread_mutex_init(&(data->die_t_m.lock), NULL))
		return (data->e_code = E_MUTEX_INIT);
	data->die_t_m.to_destroy = 1;
	if (pthread_mutex_init(&(data->n_meal_m.lock), NULL))
		return (data->e_code = E_MUTEX_INIT);
	data->n_meal_m.to_destroy = 1;
	if (pthread_mutex_init(&(data->state_m.lock), NULL))
		return (data->e_code = E_MUTEX_INIT);
	data->state_m.to_destroy = 1;
	if (pthread_mutex_init(&(data->err_code_m.lock), NULL))
		return (data->e_code = E_MUTEX_INIT);
	data->err_code_m.to_destroy = 1;
	if (pthread_mutex_init(&(data->start_sim.lock), NULL))
		return (data->e_code = E_MUTEX_INIT);
	data->start_sim.to_destroy = 1;
	return (0);
} */

static int	init_philos(t_data *data)
{
	int	i;

	data->philo = ft_calloc(data->info.n_philo, sizeof(t_philo));
	if (!data->philo)
		return (data->e_code = ERROR);
	i = -1;
	while (++i < data->info.n_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		pthread_mutex_init(&(data->philo[i].philo_mutex), NULL);
	}
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;
	int	n_philo;

	n_philo = data->info.n_philo;
	data->fork = ft_calloc(n_philo, sizeof(t_fork));
	if (!data->fork)
		return (ERROR);
	i = -1;
	while (++i < n_philo)
	{
		pthread_mutex_init(&(data->fork[i].fork), NULL);
		data->fork[i].started = true;
		data->fork[i].fork_id = i;
		data->philo[i].first_fork = &(data->fork[i]);
		data->philo[i].second_fork = &(data->fork[(i + 1) % n_philo]);
	}
	return (0);
}

int	init(t_data *data)
{
	pthread_mutex_init(&(data->data_mutex), NULL);
	pthread_mutex_init(&(data->print_mutex), NULL);
	if (init_philos(data))
		return (data->e_code);
	if (init_forks(data))
		return (data->e_code);
	return (0);
}
