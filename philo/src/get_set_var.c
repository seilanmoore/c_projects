/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:26:52 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/07 20:01:14 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_bool(t_mutex *mutex, bool *var, bool value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(t_mutex *mutex, bool *var)
{
	bool	value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	set_long(t_mutex *mutex, long *var, long value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

long	get_long(t_mutex *mutex, long *var)
{
	long	value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}

bool	simulation_ended(t_data *data)
{
	return (get_bool(&(data->data_mutex), &(data->ended)));
}
