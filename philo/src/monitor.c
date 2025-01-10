/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:14:13 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/10 12:27:39 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	philo_died(t_philo *philo)
{
	time_t	elapsed;

	if (get_bool(&(philo->philo_mutex), &(philo->full)))
		return (false);
	elapsed = get_time() - get_long(&(philo->philo_mutex), \
	&(philo->last_meal));
	if (elapsed > philo->data->info.die_t)
		return (true);
	return (false);
}

void	*monitor(void *data_)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_;
	while (!all_threads_running(&(data->data_mutex), \
	&(data->n_threads_running), data->info.n_philo))
		;
	while (!simulation_ended(data))
	{
		i = -1;
		while (++i < data->info.n_philo)
		{
			if (philo_died(&(data->philo[i])) && \
			!simulation_ended(data))
			{
				set_bool(&(data->data_mutex), &(data->ended), true);
				logs(&(data->philo[i]), DIE);
			}
		}
	}
	return (0);
}
