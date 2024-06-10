/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:11:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/11 00:44:51 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	exec_first(t_data *data)
{
	if (dup2(data->file[0].fd, STDIN_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	if (dup2(data->pipedes.fd[1], STDOUT_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	close_pipe(data, &(data->pipedes), 0);
	if (execve(data->cmd[0].path, data->cmd[0].opt, data->envp) == ERROR)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(data->cmd[0].opt[0], 2);
		ft_putstr_fd(": " EXECF "\n", 2);
		ft_error(data, NULL, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void	exec_second(t_data *data)
{
	if (dup2(data->pipedes.fd[0], STDIN_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	if (dup2(data->file[1].fd, STDOUT_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	close_pipe(data, &(data->pipedes), 1);
	if (execve(data->cmd[1].path, data->cmd[1].opt, data->envp) == ERROR)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(data->cmd[1].opt[1], 2);
		ft_putstr_fd(": " EXECF "\n", 2);
		ft_error(data, NULL, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void	buffer_here_doc(t_data *data)
{
	char	*limit;
	char	*line;

	limit = ft_strjoin(data->argv[2], "\n");
	if (!limit)
		ft_error(data, "ft_strjoin: " ALLOCF, NULL);
	line = get_next_line(STDIN_FILENO);
	if (!line)
		ft_error(data, "get_next_line: ", strerror(errno));
	while (line && ft_strncmp(line, limit, ft_strlen(line)))
	{
		ft_putstr_fd(line, data->file[0].fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (line)
		free(line);
	free(limit);
	close_file(data, &(data->file[0]));
	data->file[0].fd = open(_HERE_DOC, O_RDONLY);
	if (data->file[0].fd == ERROR)
		ft_error(data, _HERE_DOC, strerror(errno));
	data->file[0].opened = 1;
}

void	here_doc(t_data *data)
{
	buffer_here_doc(data);
	data->pid = fork();
	if (data->pid == ERROR)
		ft_error(data, FORKF, strerror(errno));
	if (data->pid == 0)
		exec_first(data);
	waitpid(data->pid, NULL, 0);
	data->pid = fork();
	if (data->pid == ERROR)
		ft_error(data, FORKF, strerror(errno));
	if (data->pid == 0)
		exec_second(data);
}
