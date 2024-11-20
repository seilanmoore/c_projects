/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:37:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/12 17:07:21 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_local_error(char	*token)
{
	ft_putstr_fd(token, 2);
	ft_putendl_fd(": " NOT_FOUND, 2);
}

int	id_error(t_data *data, char *arg, char *variable, int exp)
{
	if (variable && !valid_ident(variable))
	{
		if (!exp)
			print_local_error(arg);
		else
		{
			ft_putstr_fd(MS "`", 2);
			ft_putstr_fd(arg, 2);
			print_msg(data, "': " EXPORT_ID, 2);
		}
		return (1);
	}
	else if (!variable && !valid_ident(arg))
	{
		if (!exp)
			print_local_error(arg);
		else
		{
			ft_putstr_fd(MS "`", 2);
			ft_putstr_fd(arg, 2);
			print_msg(data, "': " EXPORT_ID, 2);
		}
		return (1);
	}
	return (0);
}

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

int	execve_error(t_data *data, t_cmd *cmd)
{
	int	code;

	code = errno;
	ft_putstr_fd(MS, 2);
	ft_putstr_fd(data->last_cmd->token, 2);
	ft_putstr_fd(": ", 2);
	if (!ft_strchr(cmd->cmd, '/'))
	{
		ft_putendl_fd(NOT_FOUND, 2);
		return (127);
	}
	else
	{
		if (!stat(data->last_cmd->token, &(data->stat)) && \
		S_ISDIR(data->stat.st_mode) && \
		ft_strchr(cmd->cmd, '/'))
			ft_putendl_fd(IS_DIR, 2);
		else
		{
			ft_putendl_fd(strerror(code), 2);
			if (code == 2)
				return (127);
		}
		return (126);
	}
}

/* int	cmd_error(t_data *data, int status, int print)
{
	if (!status)
		return (0);
	if (print)
	{
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(data->last_cmd, 2);
		ft_putstr_fd(": ", 2);
		if (!ft_strchr(data->last_cmd, '/'))
			ft_putendl_fd(NOT_FOUND, 2);
		else if (!stat(data->last_cmd, &(data->stat)) && \
		S_ISDIR(data->stat.st_mode))
			ft_putendl_fd(IS_DIR, 2);
		else
			ft_putendl_fd(strerror(status), 2);
	}
	if (status == 2 || status == 13)
	{
		if (ft_strchr(data->last_cmd, '/') && status != 2)
			return (126);
		return (127);
	}
	return (status);
} */
