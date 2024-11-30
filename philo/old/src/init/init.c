/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:42:08 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/25 10:55:02 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static int	init_data(t_data *data, char **argv, int argc)
{
	*data = (t_data){0};
	data->philo_num = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	if (pthread_mutex_init(&data->write, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->lock, NULL))
		return (ft_clear(data), EXIT_FAILURE);
	return (SUCCESS);
}

static int	alloc(t_data *data)
{
	data->tid = ft_calloc(data->philo_num, sizeof(pthread_t));
	if (!data->tid)
		return (ft_clear(data), EXIT_FAILURE);
	data->fork = ft_calloc(data->philo_num, sizeof(pthread_mutex_t));
	if (!data->fork)
		return (ft_clear(data), EXIT_FAILURE);
	data->philo = ft_calloc(data->philo_num, sizeof(t_philo));
	if (!data->philo)
		return (ft_clear(data), EXIT_FAILURE);
	return (SUCCESS);
}

static int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL))
			return (ft_clear(data), EXIT_FAILURE);
	}
	data->philo[0].l_fork = &(data->fork[0]);
	data->philo[0].r_fork = &(data->fork[data->philo_num - 1]);
	i = 0;
	while (++i < data->philo_num)
	{
		data->philo[i].l_fork = &(data->fork[i]);
		data->philo[i].r_fork = &(data->fork[i - 1]);
	}
	return (SUCCESS);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].time_to_die = data->death_time;
		if (pthread_mutex_init(&(data->philo[i].lock), NULL))
			return (ft_clear(data), EXIT_FAILURE);
	}
	return (SUCCESS);
}

int	init(t_data *data, char **argv, int argc)
{
	if (init_data(data, argv, argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (alloc(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_forks(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philos(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (SUCCESS);
}
