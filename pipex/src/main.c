/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:50:40 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/31 10:44:21 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	child(t_data *data)
{
	if (dup2(data->fd_in, STDIN_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	if (dup2(data->pipedes[1], STDOUT_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	if (close(data->pipedes[0]) == ERROR)
		ft_error(data, CLOSEF, strerror(errno));
	if (execve(data->cmd1p, data->cmd1, data->envp) == ERROR)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(data->cmd1[0], 2);
		ft_putstr_fd(": " EXECF "\n", 2);
		ft_error(data, NULL, strerror(errno));
	}
}

static void	parent(t_data *data)
{
	if (dup2(data->fd_out, STDOUT_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	if (dup2(data->pipedes[0], STDIN_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	if (close(data->pipedes[1]) == ERROR)
		ft_error(data, CLOSEF, strerror(errno));
	if (execve(data->cmd2p, data->cmd2, data->envp) == ERROR)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(data->cmd2[0], 2);
		ft_putstr_fd(": " EXECF "\n", 2);
		ft_error(data, NULL, strerror(errno));
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data = (t_data){NULL};
	init(&data, argv, envp, argc);
	data.pid = fork();
	if (data.pid == ERROR)
		ft_error(&data, FORKF, strerror(errno));
	if (data.pid == 0)
		child(&data);
	parent(&data);
	cleanup(&data);
	return (EXIT_SUCCESS);
}
