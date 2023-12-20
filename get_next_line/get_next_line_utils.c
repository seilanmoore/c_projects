/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:58:37 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/20 21:20:14 by smoore-a         ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned char	*res_str;
	size_t			full_size;
	size_t			buffer_len;

	buffer_len = 0;
	while (s2[buffer_len] != '\n' && s2[buffer_len])
		buffer_len++;
	full_size = ft_strlen(s1) + buffer_len + 1;
	res_str = (unsigned char *) malloc(sizeof(char) * full_size);
	if (!res_str)
		return (NULL);
	ft_strlcpy((char *) res_str, s1, ft_strlen(s1) + 1);
	ft_strlcat((char *) res_str, s2, full_size);
	return ((char *) res_str);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	ch;

	ch = (char)c;
	str = (char *)s;
	if (ch == '\0' && *s == '\0')
		return (str);
	while (*str)
	{
		if (*str == ch)
			return (str);
		str++;
	}
	if (ch == 0)
		return (str);
	return (NULL);
}
