/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:28:36 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/10 09:47:08 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	logs(t_philo *philo, t_state state)
{
	time_t	elapsed;

	elapsed = get_time() - philo->data->start_time;
	if (philo->full)
		return ;
	pthread_mutex_lock(&(philo->data->print_mutex));
	if (state == FORK && !simulation_ended(philo->data))
		printf("%ld\t%d has taken a fork\n", elapsed, philo->id);
	else if (state == EAT && !simulation_ended(philo->data))
		printf("%ld\t%d is eating\n", elapsed, philo->id);
	else if (state == SLEEP && !simulation_ended(philo->data))
		printf("%ld\t%d is sleeping\n", elapsed, philo->id);
	else if (state == THINK && !simulation_ended(philo->data))
		printf("%ld\t%d is thinking\n", elapsed, philo->id);
	else if (state == DIE)
		printf("%ld\t%d died\n", elapsed, philo->id);
	pthread_mutex_unlock(&(philo->data->print_mutex));
}
