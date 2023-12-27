/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:50:17 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/27 22:15:07 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size > 0)
	{
		i = 0;
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	cat_len;
	size_t	dst_len;
	size_t	i;

	cat_len = ft_strlen(src) + ft_strlen(dst);
	dst_len = 0;
	while (dst[dst_len] && dst_len < size)
		dst_len++;
	i = 0;
	if (dst_len >= size)
		return (size + ft_strlen(src));
	while (src[i] && dst_len + i + 1 < size)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (cat_len);
}

char	*ft_strjoin(char *line, char *buffer)
{
	char	*next_line;
	size_t	full_size;
	int		i;

	i = 0;
	full_size = ft_strlen(line) + ft_strlen(buffer) + 1;
	next_line = (char *)malloc(full_size * sizeof(char));
	if (!next_line)
		return (NULL);
	else
	{
		while (next_line[i])
			next_line[i++] = '\0';
		ft_strlcpy(next_line, line, full_size);
		free(line);
		ft_strlcat(next_line, buffer, full_size);
		while (*buffer)
			*buffer++ = '\0';
		return (next_line);
	}
}
