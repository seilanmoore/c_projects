/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:42:31 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/05 07:08:09 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	init_assign(t_data *data, char **argv, char **envp)
{
	data->argv = argv;
	data->envp = envp;
	data->pid = -1;
	data->fd_in = -1;
	data->fd_out = -1;
	data->pipedes[0] = -1;
	data->pipedes[1] = -1;
	data->exit_code = -1;
}

static void	check_permissions(t_data *data)
{
	int		len;
	char	*tmp;

	if (access(data->argv[1], F_OK | R_OK) == ERROR)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->argv[1], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	len = ft_strrchr(data->argv[4], '/') - data->argv[4];
	tmp = ft_substr(data->argv[4], 0, len);
	if (access(tmp, F_OK & W_OK) == ERROR)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (access(data->argv[4], (F_OK & W_OK) | W_OK) == ERROR)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->argv[4], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	free(tmp);
}

static void	open_fds(t_data *data)
{
	data->fd_in = open(data->argv[1], O_RDONLY, 0644);
	data->fd_out = open(data->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_in == ERROR || data->fd_out == ERROR)
	{
		ft_putstr_fd("bash: ", 2);
		if (data->fd_in == ERROR && data->fd_out != ERROR)
		{
			ft_putstr_fd(data->argv[1], 2);
			ft_putstr_fd("0\n", data->fd_out);
			data->exit_code = 0;
		}
		else if (data->fd_out == ERROR)
		{
			ft_putstr_fd(data->argv[4], 2);
			data->exit_code = errno;
		}
		ft_putstr_fd(OPENF, 2);
		ft_error(data, NULL, NULL);
	}
}

static void	assign_cmd(t_data *data)
{
	data->cmd1 = ft_split(data->argv[2], ' ');
	if (data->cmd1 == NULL)
		ft_error(data, "ft_split: " ALLOCF, NULL);
	data->cmd2 = ft_split(data->argv[3], ' ');
	if (data->cmd2 == NULL)
		ft_error(data, "ft_split: " ALLOCF, NULL);
}

void	init(t_data *data, char **argv, char **envp, int argc)
{
	init_assign(data, argv, envp);
	if (argc != 5)
		ft_error(data, "wrong number of arguments. Must be 4 arguments", NULL);
	if (data->envp == NULL)
		ft_error(data, "environment variables not found", NULL);
	check_permissions(data);
	open_fds(data);
	assign_cmd(data);
	get_path(data);
	if (pipe(data->pipedes) == ERROR)
		ft_error(data, PIPEF, strerror(errno));
}
