/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:38:02 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/30 19:58:45 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	logs(t_philo *philo, int state, time_t time)
{
	pthread_mutex_lock(&(philo->data->print_m.lock));
	if (state == DIE)
		printf("%ld\t%d died\n", time, philo->id);
	else if (state == FORK)
		printf("%ld\t%d has taken a fork\n", time, philo->id);
	else if (state == EAT)
		printf("%ld\t%d is eating\n", time, philo->id);
	else if (state == SLEEP)
		printf("%ld\t%d is sleeping\n", time, philo->id);
	else if (state == THINK)
		printf("%ld\t%d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&(philo->data->print_m.lock));
}

void	take_fork(t_philo *philo)
{
	time_t	start;
	time_t	time;

	start = philo->data->start_time;
	if (philo->id % 2)
		ft_usleep(200);
	pthread_mutex_lock(&(philo->data->state_m.lock));
	while (philo->data->dead == FALSE)
	{
		pthread_mutex_unlock(&(philo->data->state_m.lock));
		if (!pthread_mutex_lock(&(philo->r_fork->lock)))
		{
			time = get_time() - start;
			logs(philo, FORK, time);
			pthread_mutex_lock(&(philo->data->state_m.lock));
			while (philo->data->dead == FALSE)
			{
				pthread_mutex_unlock(&(philo->data->state_m.lock));
				if (!pthread_mutex_lock(&(philo->l_fork->lock)))
				{
					time = get_time() - start;
					logs(philo, FORK, time);
					logs(philo, EAT, time);
					ft_usleep(philo->data->info.eat_t);
					time = get_time() - start;
					pthread_mutex_unlock(&(philo->r_fork->lock));
					pthread_mutex_unlock(&(philo->l_fork->lock));
					pthread_mutex_lock(&(philo->data->state_m.lock));
					philo->last_meal = get_time();
					pthread_mutex_unlock(&(philo->data->state_m.lock));
					pthread_mutex_lock(&(philo->data->state_m.lock));
					if (philo->data->dead == FALSE)
						logs(philo, SLEEP, time);
					pthread_mutex_unlock(&(philo->data->state_m.lock));
					ft_usleep(philo->data->info.sleep_t);
					time = get_time() - start;
					pthread_mutex_lock(&(philo->data->state_m.lock));
					if (philo->data->dead == FALSE)
						logs(philo, THINK, time);
					pthread_mutex_unlock(&(philo->data->state_m.lock));
				}
			}
			if (pthread_mutex_unlock(&(philo->r_fork->lock)))
				return ;
		}
	}
	if (pthread_mutex_unlock(&(philo->data->state_m.lock)))
		return ;
}
