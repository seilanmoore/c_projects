/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 00:38:52 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/10 20:20:42 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	data = (t_data){0};
	if (check_info(&data, argc, argv))
		return (data.e_code);
	if (init(&data))
		return (cleanup(&data), data.e_code);
	start_simulation(&data);
	i = -1;
	while (++i < data.info.n_philo)
		pthread_join(data.philo[i].thread, NULL);
	set_bool(&(data.data_mutex), &(data.ended), true);
	pthread_join(data.monitor, NULL);
	pthread_join(data.meals, NULL);
	cleanup(&data);
	return (EXIT_SUCCESS);
}
