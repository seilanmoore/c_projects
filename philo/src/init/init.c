/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:42:08 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/18 11:04:18 by smoore-a         ###   ########.fr       */
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
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (SUCCESS);
}

static int	alloc(t_data *data)
{
	int	i;

	data->tid = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->tid)
		ft_error(data, PHILO EALLOC, NULL);
	i = -1;
	while (++i < data->philo_num)
		data->tid[i] = (pthread_t){0};
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->fork)
		ft_error(data, PHILO EALLOC, NULL);
	i = -1;
	while (++i < data->philo_num)
		data->fork[i] = (pthread_mutex_t){0};
	data->philo = malloc(sizeof(t_philo) * data->philo_num);
	if (data->philo == NULL)
		ft_error(data, PHILO EALLOC, NULL);
	i = -1;
	while (++i < data->philo_num)
		data->philo[i] = (t_philo){0};
	return (SUCCESS);
}

static void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_init(&(data->fork[i]), NULL);
	data->philo[0].l_fork = &(data->fork[0]);
	data->philo[0].r_fork = &(data->fork[data->philo_num - 1]);
	i = 0;
	while (++i < data->philo_num)
	{
		data->philo[i].l_fork = &(data->fork[i]);
		data->philo[i].r_fork = &(data->fork[i - 1]);
	}
}

static void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].time_to_die = data->death_time;
		pthread_mutex_init(&(data->philo[i].lock), NULL);
	}
}

int	init(t_data *data, char **argv, int argc)
{
	if (init_data(data, argv, argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (alloc(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_forks(data);
	init_philos(data);
	return (SUCCESS);
}
