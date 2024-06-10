/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:13:08 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/10 10:37:49 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	char 	*limit;

	init(&data, argc, argv, envp);
	limit = ft_strjoin(data.argv[2], "\n");
	line = get_next_line(0);
	while (line && ft_strncmp(line, limit, ft_strlen(line)))
	{
		ft_putstr_fd(line, data.file[1].fd);
		free(line);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	if (limit)
		free(limit);
	cleanup(&data);
	exit(EXIT_SUCCESS);
}
