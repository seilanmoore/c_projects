/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:29:42 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/09 20:31:36 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	get_time(void)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (print_msg(E_GET_TIME, E_TIME));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(time_t ms, t_data *data)
{
	time_t	start;
	time_t	elapsed;
	time_t	remain;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		if (simulation_ended(data))
			break ;
		elapsed = get_time() - start;
		remain = ms - elapsed;
		if (remain > 1)
			usleep(1000);
		else
		{
			while ((get_time() - start) < ms)
				;
		}
	}
}
