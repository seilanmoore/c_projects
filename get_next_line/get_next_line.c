/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:58:31 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/20 21:47:02 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffer;
	size_t	read_bytes;

	read_bytes = 1;
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = "";
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	while (!ft_strchr(buffer, 10) && read_bytes > 0)
	{
		line = ft_strjoin(line, buffer);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (!line)
	{
		free(buffer);
		free(line);
		return(NULL);
	}
	return (line);
}

int main(int argc, char *argv[])
{
	int	i;
	int	lines;
	int	fname;

	i = 1;
	lines = 0;
	fname = 0;
	if(argc < 2)
	{
		printf("Introduce an argument.\n");
		return (0);
	}
	while (argc-- > 1)
	{
		fname = open(argv[i++], O_RDONLY);
		while (lines++ < 5)
			printf("The %d is %s\n", lines, get_next_line(fname));
	}
	close(fname);
	return (0);
}