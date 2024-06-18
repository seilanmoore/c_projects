/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 22:53:41 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/18 11:57:03 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 5 && argc != 6)
		return (ft_error(NULL, PHILO USAGE ARGS OPTIONAL, NULL));
	if (check_args(argc, argv) == ERROR)
		return (EXIT_FAILURE);
	if (init(&data, argv, argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (data.philo_num == 1)
		return (case_one(&data));
	if (simulation(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_clear(&data);
	return (EXIT_SUCCESS);
}
