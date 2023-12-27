/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 08:51:54 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/27 22:35:55 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strdup(const char *s1)
{
	unsigned char	*str;
	size_t			s1_len;

	s1_len = ft_strlen(s1) + 1;
	str = (unsigned char *) malloc(s1_len * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy((char *) str, s1, s1_len);
	return ((char *) str);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub_s = (char *)malloc((len + 1) * sizeof(char));
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
	{
		line = (char *)malloc(sizeof(char));
		*line = '\0';
	}
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
	static char	*line = NULL;
	char		*buffer;
	int			read_bytes;

	line = clean_line(line);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (line)
	{
		read_bytes = 1;
		while (!ft_strchr(line, '\n') && read_bytes > 0)
		{
			read_bytes = read(fd, buffer, BUFFER_SIZE);
			line = ft_strjoin(line, buffer);
			if (!line)
			{
				free(buffer);
				return (NULL);
			}
		}
	}
	free(buffer);
	buffer = NULL;
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
		next_line = get_next_line(fname);
	}
	close(fname);
	return (0);
} */
