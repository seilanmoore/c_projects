/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:00:05 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/24 18:55:43 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	ft_error(void *data, char *message, void *aux)
{
	if (message)
	{
		write(2, message, ft_strlen(message));
		if (aux)
		{
			write(2, ": ", 2);
			write(2, aux, ft_strlen(aux));
		}
		write(2, "\n", 1);
	}
	ft_clear(data);
	return (EXIT_FAILURE);
}
