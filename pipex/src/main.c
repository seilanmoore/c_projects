/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:50:40 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/05 22:33:38 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdlib.h>

static void	exec_second(t_data *data)
{
	int	prueba;

	prueba = 5;
	while (prueba < 10)
		ft_printf("%d", prueba++);
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
	exit(EXIT_FAILURE);
}

static void	exec_first(t_data *data)
{
	int	prueba;

	prueba = 0;
	while (prueba < 5)
		ft_printf("%d", prueba++);
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
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		pid1;
	int		pid2;

	data = (t_data){NULL};
	init(&data, argv, envp, argc);
	pid1 = fork();
	if (pid1 == ERROR)
		ft_error(&data, FORKF, strerror(errno));
	if (pid1 == 0)
		exec_first(&data);
	waitpid(pid1, NULL, 0);
	pid2 = fork();
	if (pid2 == ERROR)
		ft_error(&data, FORKF, strerror(errno));
	if (pid2 == 0)
		exec_second(&data);
	waitpid(pid2, NULL, 0);
	cleanup(&data);
	exit(EXIT_SUCCESS);
}
