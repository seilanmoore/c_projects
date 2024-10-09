/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:11:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/12 20:17:51 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
			ft_putstr_fd(line, data->fd[0]);
			free(line);
			line = get_next_line(STDIN_FILENO);
		}
		if (line)
			free(line);
		free(limit);
		close(data->fd[0]);
		data->fd[0] = open(_HERE_DOC, O_RDONLY);
		if (data->fd[0] == ERROR)				
			ft_error(data, _HERE_DOC, strerror(errno));
}

static void	exec_first(t_data *data)
{
	close(data->fd[1]);
	close(data->pipedes[0]);
	if (dup2(data->fd[0], STDIN_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	if (dup2(data->pipedes[1], STDOUT_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	close(data->fd[0]);
	close(data->pipedes[1]);
	if (execve(data->cmd[0].path, data->cmd[0].opt, data->envp) == ERROR)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(data->cmd[0].opt[0], 2);
		ft_putstr_fd(": " EXECF, 2);
		ft_error(data, NULL, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void	exec_second(t_data *data)
{
	if (dup2(data->pipedes[0], STDIN_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	if (dup2(data->fd[1], STDOUT_FILENO) == ERROR)
		ft_error(data, DUPF, strerror(errno));
	close(data->pipedes[0]);
	close(data->fd[1]);
	if (execve(data->cmd[1].path, data->cmd[1].opt, data->envp) == ERROR)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(data->cmd[1].opt[0], 2);
		ft_putstr_fd(": " EXECF ": ", 2);
		ft_error(data, NULL, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	here_doc(t_data *data)
{
	pid_t	pid[2];

	buffer_here_doc(data);
	if (pipe(data->pipedes) == ERROR)
		ft_error(data, PIPEF, strerror(errno));
	pid[0] = fork();
	if (pid[0] == ERROR)
		ft_error(data, FORKF, strerror(errno));
	if (pid[0] == 0)
		exec_first(data);
	close(data->fd[0]);
	close(data->pipedes[1]);
	waitpid(pid[0], NULL, 0);
	pid[1] = fork();
	if (pid[1] == ERROR)
		ft_error(data, FORKF, strerror(errno));
	if (pid[1] == 0)
		exec_second(data);
	close(data->pipedes[0]);
	close(data->fd[1]);
	waitpid(pid[1], NULL, 0);
}
