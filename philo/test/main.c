/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:01:51 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/24 21:29:10 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include <pthread.h>
#include <time.h>

void	routine(void *n_thread)
{
	int	*n;

	n = (int *)n_thread;
	printf("Test from thread %d\n", *n + 1);
	sleep(2);
	printf("Ending from thread %d\n", *n + 1);
}

int	main(int argc, char **argv)
{
	pthread_t	t1, t2;
	int			i, j;

	i = 0;
	if (pthread_create(&t1, NULL, (void *)routine, &i) != 0)
		return (1);
	i = 99;
	if (pthread_create(&t2, NULL, (void *)routine, &i) != 0)
		return (1);
	i = 0;
	if (pthread_join(t1, NULL) != 0)
		return (1);
	if (pthread_join(t2, NULL) != 0)
		return (1);
	return (0);
}
