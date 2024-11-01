/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:35:09 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/01 14:25:04 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	write_heredoc(t_data *data)
{
	char	*limiter;
	char	*line;

	close(data->l_pipe[0]);
	limiter = data->heredoc;
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strcmp(line, limiter))
	{
		write(data->l_pipe[1], line, ft_strlen(line));
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(data->l_pipe[1]);
	return (0);
}
