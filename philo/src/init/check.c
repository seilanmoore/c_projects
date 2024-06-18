/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:19:38 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/18 11:04:14 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	check_args(int argc, char **argv)
{
	int	i;

	if (ft_atoi(argv[1]) < 1)
		return (ft_error(NULL, PHILO INVALID, argv[1]), ERROR);
	i = 1;
	while (++i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (ft_error(NULL, PHILO INVALID, argv[i]), ERROR);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (ft_error(NULL, PHILO INVALID, argv[5]), ERROR);
	return (SUCCESS);
}
