/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 08:51:54 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/29 16:26:13 by smoore-a         ###   ########.fr       */
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
	size_t	i;
	char	*sub_s;

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
	size_t	i;
	char	*right_str;

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

	free(next_line);
	next_line = NULL;
	if (*line != '\0' && read_bytes != -1)
	{
		i = 0;
		while (line[i] && line[i] != '\n')
			i++;
		if (line[i] == '\n')
			i++;
		next_line = ft_substr(line, 0, i);
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;
	char		*next_line;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
		line = ft_calloc(1, sizeof(char));
	read_bytes = BUFFER_SIZE;
	while (!ft_strchr(line, '\n') && read_bytes == BUFFER_SIZE)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes > 0)
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
	int		i;
	int		fname;
	char	**next_line;

	i = 0;
	fname = open("empty.txt", O_RDONLY);
	next_line = (char **)malloc(100 * sizeof(char *));
	next_line[i] = get_next_line(fname);
	while (next_line[i])
	{
		printf("%s", next_line[i]);
		next_line[++i] = get_next_line(fname);
	}
	while (i-- > 0)
		free(next_line[i]);
	free(next_line);
	close(fname);
	return (0);
}
