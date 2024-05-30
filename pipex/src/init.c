/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:42:31 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/30 17:16:42 by smoore-a         ###   ########.fr       */
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

static void	open_fds(t_data *data)
{
	data->fd_in = open(data->argv[1], O_RDONLY, 644);
	if (data->fd_in == ERROR)
		ft_error(data, OPENF, strerror(errno));
	data->fd_out = open(data->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out == ERROR)
		ft_error(data, OPENF, strerror(errno));
}

void	init(t_data *data, char **argv, char **envp)
{
	init_assign(data, argv, envp);
	assign_cmd(data);
	get_path(data);
	open_fds(data);
	if (pipe(data->pipedes) == ERROR)
		ft_error(data, PIPEF, strerror(errno));
}
