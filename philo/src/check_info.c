/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:08:40 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/27 20:39:00 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	set_info(t_data *data, char **argv)
{
	data->info.n_philo = ft_atoi(argv[1]);
	data->info.die_t = ft_atoi(argv[2]);
	data->info.eat_t = ft_atoi(argv[3]);
	data->info.sleep_t = ft_atoi(argv[4]);
	if (argv[5])
		data->info.n_meal = ft_atoi(argv[5]);
	else
		data->info.n_meal = -1;
}

int	check_info(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (data->e_code = print_msg(E_ARG PRO EXE ARGS OPT, E_INFO));
	set_info(data, argv);
	if (data->info.n_philo <= 0 || data->info.n_philo > 200)
		return (data->e_code = print_msg(E_ARG_N_PHILO, E_INFO));
	if (data->info.die_t < 60)
		return (data->e_code = print_msg(E_ARG_DIE_TIME, E_INFO));
	if (data->info.eat_t < 60)
		return (data->e_code = print_msg(E_ARG_EAT_TIME, E_INFO));
	if (data->info.sleep_t < 60)
		return (data->e_code = print_msg(E_ARG_SLEEP_TIME, E_INFO));
	if (data->info.n_meal < -1)
		return (data->e_code = print_msg(E_ARG_N_MEALS, E_INFO));
	return (0);
}
