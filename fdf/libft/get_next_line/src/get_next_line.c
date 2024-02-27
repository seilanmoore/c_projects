/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:00:16 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/27 22:19:47 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

static char	*ft_strdup(char *str)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc((str_len(str) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = -1;
	while (str[++i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

static char	*get_new_cache(char *cache, char *line)
{
	char	*new_cache;
	char	*temp;

	if (!line)
	{
		free(cache);
		return (NULL);
	}
	if (found_nl(cache))
	{
		temp = found_nl(cache) + 1;
		if (*temp != '\0')
		{
			new_cache = ft_strdup(temp);
			free(cache);
			return (new_cache);
		}
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
		if (found_nl(cache))
			end = found_nl(cache) - cache + 1;
		else
			end = str_len(cache);
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
	static char	*cache = NULL;
	char		*line;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (cache)
			free(cache);
		return (NULL);
	}
	cache = get_buffer(fd, cache, &read_bytes);
	if (!cache)
		return (NULL);
	while (!found_nl(cache) && read_bytes > 0)
	{
		cache = get_buffer(fd, cache, &read_bytes);
		if (!cache)
			return (NULL);
	}
	line = get_new_line(cache);
	cache = get_new_cache(cache, line);
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("tests/41_with_nl", O_RDONLY);
	line = "";
	while (line)
	{
		line = get_next_line(100);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
	}
	close(fd);
	return (0);
} */
