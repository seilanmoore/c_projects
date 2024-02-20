/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:00:16 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/20 18:29:51 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strdup(char *str)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = -1;
	while (str[++i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

static char	*get_new_cache(char *cache)
{
	char	*new_cache;
	char	*temp;

	temp = found_nl(cache);
	if (*temp == '\n')
		temp++;
	if (*temp != '\0')
	{
		new_cache = ft_strdup(temp);
		free(cache);
		return (new_cache);
	}
	free(cache);
	return (NULL);
}

static char	*get_new_line(char *cache)
{
	int		i;
	int		end;
	char	*new_line;

	if (*cache != '\0')
	{
		if (*found_nl(cache) != '\0')
			end = found_nl(cache) - cache + 1;
		else
			end = ft_strlen(cache);
		new_line = (char *)malloc((end + 1) * sizeof(char));
		if (!new_line)
			return (NULL);
		i = -1;
		while (++i < end)
			new_line[i] = cache[i];
		new_line[i] = '\0';
		return (new_line);
	}
	return (NULL);
}

static char	*get_buffer(int fd, char *cache, int *read_bytes)
{
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		if (cache)
			free(cache);
		return (NULL);
	}
	*read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (*read_bytes == -1)
	{
		if (cache)
			free(cache);
		free(buffer);
		return (NULL);
	}
	buffer[*read_bytes] = '\0';
	if (!cache && !(*read_bytes))
		cache = NULL;
	else if (*read_bytes > 0)
		cache = extend_cache(cache, buffer);
	free(buffer);
	return (cache);
}

char	*get_next_line(int fd)
{
	static char	*cache[20];
	char		*line;
	int			read_bytes;

	if (fd < 0 || fd > 19 || BUFFER_SIZE <= 0)
		return (NULL);
	cache[fd] = get_buffer(fd, cache[fd], &read_bytes);
	if (!cache[fd])
		return (NULL);
	while (*found_nl(cache[fd]) == '\0' && read_bytes > 0)
	{
		cache[fd] = get_buffer(fd, cache[fd], &read_bytes);
		if (!cache[fd])
			return (NULL);
	}
	line = get_new_line(cache[fd]);
	cache[fd] = get_new_cache(cache[fd]);
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("tests/variable_nls.txt", O_RDONLY);
	printf("FOPEN_MAX = %d\n", FOPEN_MAX);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
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
