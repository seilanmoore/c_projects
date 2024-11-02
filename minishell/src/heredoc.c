/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:35:09 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/02 14:42:38 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

int	write_heredoc(t_data *data)
{
	int		pid;
	char	*limiter;
	char	*line;
	char	*no_endl;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (data->l_pipe[0] != -1)
			close(data->l_pipe[0]);
		limiter = data->heredoc;
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		no_endl = ft_substr(line, 0, ft_strlen(line) - 1);
		while (line && ft_strcmp(no_endl, limiter))
		{
			write(data->l_pipe[1], line, ft_strlen(line));
			write(STDOUT_FILENO, "> ", 2);
			free(line);
			line = get_next_line(STDIN_FILENO);
			free(no_endl);
			no_endl = ft_substr(line, 0, ft_strlen(line) - 1);
		}
		free(line);
		free(no_endl);
		exit (0);
	}
	waitpid(pid, NULL, 0);
	return (0);
}
