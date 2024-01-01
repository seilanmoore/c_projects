/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:00:16 by smoore-a          #+#    #+#             */
/*   Updated: 2024/01/01 22:18:18 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strdup(char *str)
{
	char	*dup;
	size_t	i;

	if (!str)
	{
		dup = (char *)malloc(1 * sizeof(char));
		*dup = '\0';
		return (dup);
	}
	dup = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = -1;
	while (str[++i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

static char	*get_new_cache(char *cache, int start)
{
	char	*new_cache;

	if (*cache != '\0')
	{
		new_cache = ft_strdup(&cache[start]);
		free(cache);
		cache = NULL;
		return (new_cache);
	}
	free(cache);
	cache = NULL;
	return (NULL);
}

static char	*get_new_line(char *cache, int start)
{
	int		i;
	char	*new_line;

	if (*cache != '\0')
	{
		new_line = (char *)malloc((start + 1) * sizeof(char));
		if (!new_line)
			return (NULL);
		i = -1;
		while (++i < start)
			new_line[i] = cache[i];
		new_line[i] = '\0';
		return (new_line);
	}
	return (NULL);
}

static char	*get_buffer(int fd, char *cache, char *buffer, int *read_bytes)
{
	*read_bytes = read(fd, buffer, BUFFER_SIZE);
	buffer[*read_bytes] = '\0';
	if (!cache && !(*read_bytes))
		return (ft_strdup(cache));
	else if (cache && *read_bytes == -1)
	{
		free(cache);
		return (NULL);
	}
	else if (*read_bytes)
		return (extend_cache(cache, buffer));
	else
		return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*cache = NULL;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	*buffer = '\0';
	read_bytes = 1;
	cache = get_buffer(fd, cache, buffer, &read_bytes);
	if (!cache)
		return (NULL);
	while (found_nl(cache) == -1 && read_bytes == BUFFER_SIZE)
	{
		cache = get_buffer(fd, cache, buffer, &read_bytes);
		if (!cache)
			return (NULL);
	}
	line = get_new_line(cache, found_nl(cache) + 1);
	cache = get_new_cache(cache, found_nl(cache) + 1);
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
	}
	close(fd);
	return (0);
} */
