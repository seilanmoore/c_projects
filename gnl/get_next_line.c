/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 08:51:54 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/28 22:08:16 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	sub_s = ft_calloc(len + 1, sizeof(char));
	if (!sub_s)
		return (NULL);
	while (i < len && (sub_s[i] || s[start]))
		sub_s[i++] = s[start++];
	sub_s[i] = '\0';
	return (sub_s);
}

static char	*right_str(char	*line, int read_bytes)
{
	char	*right_str;
	size_t	i;

	if (read_bytes > 0)
	{
		i = 0;
		while (line[i] && line[i] != '\n')
			i++;
		if (line[i] == '\n')
			i++;
		right_str = ft_substr(line, i, (ft_strlen(line) - i) + 1);
		free(line);
		line = NULL;
		return (right_str);
	}
	free(line);
	return (NULL);
}

static char	*left_str(char	*line, char *next_line, int read_bytes)
{
	size_t	i;

	if (line)
	{
		if (read_bytes > 0)
		{
			i = 0;
			while (line[i] && line[i] != '\n')
				i++;
			if (line[i] == '\n')
				i++;
			next_line = ft_substr(line, 0, i);
			return (next_line);
		}
		free(next_line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;
	int			read_bytes;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
		line = ft_calloc(1, sizeof(char));
	read_bytes = BUFFER_SIZE;
	while (!ft_strchr(line, '\n') && read_bytes == BUFFER_SIZE)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		line = ft_strjoin(line, buffer);
		free(buffer);
	}
	next_line = ft_calloc(1, sizeof(char));
	next_line = left_str(line, next_line, read_bytes);
	line = right_str(line, read_bytes);
	return (next_line);
}

int	main(void)
{
	int		fname;
	char	*next_line;

	fname = open("a.txt", O_RDONLY);
	next_line = get_next_line(fname);
	while (next_line)
	{
		printf("%s", next_line);
		next_line = get_next_line(fname);
	}
	close(fname);
	return (0);
}
