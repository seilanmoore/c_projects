/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:35:09 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/04 17:24:41 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	write_heredoc(t_data *data)
{
	int		pid;
	char	*limiter;
	char	*line;
	char	*endl;

	pid = fork();
	if (pid == -1)
		return (1);
	g_signal = pid;
	if (pid == 0)
	{
		if (data->l_pipe[0] != -1)
			close(data->l_pipe[0]);
		limiter = data->heredoc;
		line = readline("> ");
		if (errno == EINTR)
			exit (130);
		if (!line)
			exit (1);
		endl = ft_strjoin(line, "\n");
		while (line && ft_strcmp(line, limiter))
		{
			write(data->l_pipe[1], endl, ft_strlen(endl));
			ft_free(&line);
			line = readline("> ");
			free(endl);
			if (errno == EINTR)
				exit (130);
			if (!line)
				exit (1);
			endl = ft_strjoin(line, "\n");
		}
		free(line);
		free(endl);
		exit (0);
	}
	waitpid(pid, &(data->status), 0);
	if (WEXITSTATUS(data->status) == 1)
		exit_builtin(data, NULL);
	if (WEXITSTATUS(data->status) == 130)
		return (130);
	g_signal = 0;
	return (0);
}
