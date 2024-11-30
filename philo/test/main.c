/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:39:32 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/26 20:50:19 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				cont = 0;
pthread_mutex_t	lock;

void	*routine()
{
	int	i;

	i = -1;
	while (++i < 1000000)
	{
		pthread_mutex_lock(&lock);
		if (cont == 1015000)
			printf("Ha llegado a 1015000. Valor actual %d\n", cont);
		cont++;
		pthread_mutex_unlock(&lock);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	tid1, tid2;

	pthread_mutex_init(&lock, NULL);
	pthread_create(&tid1, NULL, &routine, NULL);
	pthread_create(&tid2, NULL, &routine, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_mutex_destroy(&lock);
	printf("cont: %d\n", cont);
}
