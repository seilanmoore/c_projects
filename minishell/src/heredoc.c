/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:35:09 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/12 14:56:49 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

static void	open_heredoc(t_data *data)
{
	char	*limiter;
	char	*line;
	char	*endl;

	if (data->l_pipe[0] != -1)
		close(data->l_pipe[0]);
	limiter = data->heredoc;
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(1);
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		expand_later(data, &line);
		endl = ft_strjoin(line, "\n");
		write(data->l_pipe[1], endl, ft_strlen(endl));
		free(line);
		free(endl);
	}
	exit(0);
}

int	write_heredoc(t_data *data)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		return (1);
	g_signal = pid;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		open_heredoc(data);
	}
	waitpid(pid, &(data->status), 0);
	if (!WIFEXITED(data->status))
		return (130);
	else if (WEXITSTATUS(data->status) == 1)
		exit_builtin(data, NULL);
	return (0);
}
