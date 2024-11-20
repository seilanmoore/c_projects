/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:00:05 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/20 10:22:31 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <unistd.h>

int	ft_error(void *data, char *message, void *aux)
{
	if (message)
	{
		write(STDOUT_FILENO, message, ft_strlen(message));
		if (aux)
		{
			write(STDOUT_FILENO, ": ", 2);
			write(STDOUT_FILENO, aux, ft_strlen(aux));
		}
		write(STDOUT_FILENO, "\n", 1);
	}
	ft_clear(data);
	return (EXIT_FAILURE);
}
