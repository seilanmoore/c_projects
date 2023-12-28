/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 08:51:54 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/28 13:27:52 by smoore-a         ###   ########.fr       */
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

	if (!s)
		return (NULL);
	sub_s = ft_calloc((len + 1) * sizeof(char), 1);
	if (!sub_s)
		return (NULL);
	while (len-- > 0 && (sub_s[start] || s[start]))
	{
		sub_s[start] = s[start];
		start++;
	}
	sub_s[start] = '\0';
	return (sub_s);
}

static char	*eol(char	*line)
{
	size_t	i;

	if (line)
	{
		i = 0;
		while (line[i] && line[i] != '\n')
			i++;
		if (line[i] == '\n')
			i++;
		return (ft_substr(line, 0, i));
	}
	return (NULL);
}

static char	*clean_line(char *line)
{
	if (!line)
		line = ft_calloc(1 * sizeof(char), 1);
	else
	{
		if (ft_strchr(line, '\n') && *(ft_strchr(line, '\n') + 1) != '\0')
			line = ft_strchr(line, '\n') + 1;
		else
		{
			free(line);
			line = NULL;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;
	int			read_bytes;

	line = clean_line(line);
	buffer = ft_calloc((BUFFER_SIZE + 1) * sizeof(char), 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0 || !buffer)
		return (NULL);
	if (line)
	{
		read_bytes = 1;
		while (!ft_strchr(line, '\n') && read_bytes > 0)
		{
			read_bytes = read(fd, buffer, BUFFER_SIZE);
			if (read_bytes < 0)
			{
				free(buffer);
				return (NULL);
			}
			buffer[read_bytes] = '\0';
			line = ft_strjoin(line, buffer);
		}
	}
	free(buffer);
	return (eol(line));
}

/* int	main(void)
{
	int		fname;
	char	*next_line;

	fname = open("a.txt", O_RDONLY);
	next_line = get_next_line(fname);
	while (next_line)
	{
		printf("%s", next_line);
		free(next_line);
		next_line = get_next_line(fname);
	}
	close(fname);
	return (0);
} */
