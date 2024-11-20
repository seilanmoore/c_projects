/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:14 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/11 16:26:40 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_lines(void)
{
	char	*line;
	int		fd;
	int		i;

	fd = open("/tmp/.ms_history", O_RDONLY);
	if (fd == -1)
		return (handle_errno("/tmp/.ms_history"));
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		free(line);
	}
	return (i);
}

static void	put_history(int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_putnbr_fd(i++, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(line, STDOUT_FILENO);
		free(line);
	}
}

int	history_builtin(void)
{
	char	*line;
	int		fd;
	int		i;

	i = count_lines() - 500;
	fd = open("/tmp/.ms_history", O_RDONLY);
	if (fd == -1)
		return (handle_errno("/tmp/.ms_history"));
	if (i > 0)
	{
		while (i-- > 0)
		{
			line = get_next_line(fd);
			if (!line)
				break ;
			free(line);
		}
	}
	put_history(fd);
	close(fd);
	return (0);
}
