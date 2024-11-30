/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:05:47 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/30 12:38:41 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_threads(t_data *data)
{
	int			i;
	int			j;

	i = -1;
	data->start_time = get_time();
	while (++i < data->info.n_philo)
	{
		if (pthread_create(&(data->philo[i].thread), \
		NULL, &routine, &(data->philo[i])))
		{
			j = -1;
			while (++j < i)
				pthread_join(data->philo[i].thread, NULL);
			return (data->e_code = E_THREAD_CREATE);
		}
	}
	return (0);
}

static int	init_locks(t_data *data)
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
	return (0);
}

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
	}
	return (0);
}

//After loop initiating forks
/* if (n_philo == 1)
	data->philo[0].l_fork = NULL; */

static int	init_forks(t_data *data)
{
	int	i;
	int	n_philo;

	n_philo = data->info.n_philo;
	data->fork = ft_calloc(n_philo, sizeof(t_mutex));
	if (!data->fork)
		return (ERROR);
	i = -1;
	while (++i < n_philo)
	{
		if (pthread_mutex_init(&(data->fork[i].lock), NULL))
			return (data->e_code = E_MUTEX_INIT);
		data->fork[i].to_destroy = 1;
		data->philo[i].r_fork = &(data->fork[(i - 1 + n_philo) % n_philo]);
		data->philo[i].l_fork = &(data->fork[i]);
	}
	return (0);
}

int	init(t_data *data)
{
	if (init_locks(data))
		return (data->e_code);
	if (init_philos(data))
		return (data->e_code);
	if (init_forks(data))
		return (data->e_code);
	if (init_threads(data))
		return (data->e_code);
	return (0);
}
