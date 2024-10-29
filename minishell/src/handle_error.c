/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:37:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/29 10:06:30 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_errno(char *wildcard)
{
	if (errno)
	{
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(wildcard, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

int	change_status(int status)
{
	if (status == ENOENT)
		return (127);
	else
		return (126);
}

int	cmd_error(char *cmd, int status, int print)
{
	if (print)
	{
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (status == ENOENT)
	{
		if (!ft_strchr(cmd, '/'))
		{
			if (print)
			{
				ft_putstr_fd("command not found", 2);
				ft_putendl_fd(": 127", 2);
			}
		}
		else
		{
			if (print)
				ft_putendl_fd(strerror(status), 2);
		}
		return (127);
	}
	else
	{
		if (print)
			ft_putendl_fd(strerror(status), 2);
		return (126);
	}
}
