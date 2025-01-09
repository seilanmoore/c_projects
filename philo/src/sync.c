/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:34:18 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/09 20:38:46 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	all_threads_running(t_mutex *mutex, int *n_thread, int n_philo)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*n_thread == n_philo)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	increase_running_threads(t_mutex *mutex, int *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

void	sync_threads(t_data *data)
{
	while (!get_bool(&(data->data_mutex), &(data->threads_ready)))
		;
}
