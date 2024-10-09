/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:50:27 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/09 09:08:07 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int	path_f_check(char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": " PATH_EXIST, 2);
		return (1);
	}
	return (0);
}

int	path_r_check(char *path)
{
	if (access(path, R_OK) == -1)
	{
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": " PERMIT, 2);
		return (1);
	}
	return (0);
}

int	path_w_check(char *path)
{
	if (access(path, W_OK) == -1)
	{
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": " PERMIT, 2);
		return (1);
	}
	return (0);
}
