/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:22:32 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/31 10:16:20 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	ft_error(t_data *data, char *message, char *sys_error)
{
	int	exit_code;

	exit_code = data->exit_code;
	if (message || sys_error)
	{
		if (message)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(message, 2);
			if (sys_error)
				ft_putstr_fd(" -- ", 2);
		}
		if (sys_error)
			ft_putstr_fd(sys_error, 2);
		ft_putchar_fd('\n', 2);
	}
	if (exit_code != -1)
	{
		cleanup(data);
		exit(exit_code);
	}
	cleanup(data);
	exit(EXIT_FAILURE);
}
