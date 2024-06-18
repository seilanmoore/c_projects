/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_related.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:02:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/18 11:56:41 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

time_t	get_time(void)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL) == ERROR)
		return (write (2, EGETTIME, 32));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(time_t time)
{
	time_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}
