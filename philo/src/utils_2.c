/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:13:54 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/10 12:30:42 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, total_size);
	return (ptr);
}

/* void	reassign_forks(t_mutex **fork_x, t_mutex **fork_y, t_philo *philo)
{
	if (philo->first_fork->fork_id > philo->second_fork->fork_id)
	{
		*fork_x = &(philo->first_fork->fork);
		*fork_y = &(philo->second_fork->fork);
	}
	else
	{
		*fork_y = &(philo->first_fork->fork);
		*fork_x = &(philo->second_fork->fork);
	}
} */
