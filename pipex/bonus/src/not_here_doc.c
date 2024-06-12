/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:24:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/12 20:44:26 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	infile_to_cmd(t_data *data, int i)
{
	if (dup2(data->fd[0], STDIN_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	if (dup2(data->pipes[0].fd[1], STDOUT_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	close(data->pipes[0].fd[0]);
	close(data->pipes[0].fd[1]);
	close(data->fd[0]);
	if (execve(data->cmd[i].path, data->cmd[i].opt, data->envp) == ERROR)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(data->cmd[i].opt[0], 2);
		ft_putstr_fd(": " EXECF, 2);
		ft_error(data, NULL, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void	cmd_to_cmd(t_data *data, int i)
{
	if (dup2(data->pipes[i - 1].fd[0], STDIN_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	if (dup2(data->pipes[i].fd[1], STDOUT_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	close(data->pipes[i - 1].fd[0]);
	close(data->pipes[i].fd[1]);
	if (execve(data->cmd[i].path, data->cmd[i].opt, data->envp) == ERROR)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(data->cmd[i].opt[0], 2);
		ft_putstr_fd(": " EXECF, 2);
		ft_error(data, NULL, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void	cmd_to_outfile(t_data *data, int i)
{
	if (dup2(data->pipes[i - 1].fd[0], STDIN_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	if (dup2(data->fd[1], STDOUT_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	close(data->pipes[i - 1].fd[0]);
	close(data->fd[1]);
	if (execve(data->cmd[i].path, data->cmd[i].opt, data->envp) == ERROR)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(data->cmd[i].opt[0], 2);
		ft_putstr_fd(": " EXECF, 2);
		ft_error(data, NULL, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void	create_child(t_data *data, pid_t *pid, int i)
{
	if (i != data->cmdc - 1)
	{
		if (pipe(data->pipes[i].fd) == ERROR)
			ft_error(data, PIPEF, strerror(errno));
	}
	*pid = fork();
	if (*pid == ERROR)
		ft_error(data, FORKF, strerror(errno));
	if (*pid == 0)
	{
		if (i == 0)
			infile_to_cmd(data, i);
		else if (i < data->cmdc - 1)
			cmd_to_cmd(data, i);
		else
			cmd_to_outfile(data, i);
	}
	close(data->pipes[i].fd[1]);
	if (i == 0)
		close(data->fd[0]);
	else
		close(data->pipes[i - 1].fd[0]);
	if (i == data->cmdc - 1)
		close(data->fd[1]);
}

void	not_here_doc(t_data *data)
{
	pid_t	*pid;
	int		i;

	pid = ft_calloc(data->cmdc + 1, sizeof(pid_t));
	if (pid == NULL)
		ft_error(data, "ft_calloc: " ALLOCF, strerror(errno));
	data->pipes = ft_calloc(data->cmdc, sizeof(t_pipe));
	if (data->pipes == NULL)
		ft_error(data, "ft_calloc: " ALLOCF, NULL);
	i = -1;
	while (++i < data->cmdc)
	{
		create_child(data, &(pid[i]), i);
		waitpid(pid[i], NULL, 0);
	}
	free(data->pipes);
	free(pid);
}
