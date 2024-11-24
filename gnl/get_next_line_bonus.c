/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:00:16 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/13 11:25:34 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static char	*get_new_cache(char **cache)
{
	char	*new_cache;
	char	*temp;

	temp = found_nl(*cache);
	if (*temp == '\n')
		temp++;
	if (*temp != '\0')
	{
		new_cache = ft_strdup(temp);
		free_str(cache);
		return (new_cache);
	}
	return (free_str(cache));
}

static char	*get_new_line(char **cache)
{
	int		i;
	int		end;
	char	*new_line;

	if (**cache != '\0')
	{
		if (*found_nl(*cache) != '\0')
			end = found_nl(*cache) - *cache + 1;
		else
			end = str_len(*cache);
		new_line = (char *)malloc((end + 1) * sizeof(char));
		if (!new_line)
			return (free_str(cache));
		i = -1;
		while (++i < end)
			new_line[i] = (*cache)[i];
		new_line[i] = '\0';
		return (new_line);
	}
	return (free_str(cache));
}

static char	*get_buffer(int fd, char **cache, int *read_bytes)
{
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_str(cache));
	*read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (*read_bytes == -1)
		return (free_str(cache), free_str(&buffer));
	buffer[*read_bytes] = '\0';
	if (!(*cache) && !(*read_bytes))
		*cache = NULL;
	else if (*read_bytes > 0)
		*cache = extend_cache(cache, buffer);
	free_str(&buffer);
	return (*cache);
}

char	*get_next_line(int fd)
{
	static char	*cache[4096];
	char		*line;
	int			read_bytes;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	cache[fd] = get_buffer(fd, &(cache[fd]), &read_bytes);
	if (!cache[fd])
		return (NULL);
	while (*found_nl(cache[fd]) == '\0' && read_bytes > 0)
	{
		cache[fd] = get_buffer(fd, &(cache[fd]), &read_bytes);
		if (!cache[fd])
			return (NULL);
	}
	line = get_new_line(&(cache[fd]));
	if (!line)
		return (NULL);
	cache[fd] = get_new_cache(&(cache[fd]));
	return (line);
}

int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	fd = open("/home/smoore-a/Downloads/duoshell/lorem.txt", O_RDONLY);
	printf("Counting lines\n");
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free (line);
		i++;
	}
	printf("Result: %d lines\n", i);
	close(fd);
	return (0);
}
