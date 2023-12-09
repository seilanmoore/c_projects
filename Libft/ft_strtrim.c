/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:04:59 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/09 19:40:36 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* static char	*rev_str(char *s)
{
	char			*str;
	size_t			i;
	size_t			str_len;

	i = 0;
	str_len = ft_strlen(s);
	str = ft_strdup(s);
	if (!str)
		return (NULL);
	while (str_len > 0)
		str[i++] = s[--str_len];
	str[i] = '\0';
	return ((char *) str);
}

static char	*check(char *str, char *set, size_t i)
{
	while (*str && set[i])
	{
		i = 0;
		while (*str != set[i] && set[i])
			i++;
		if (set[i] != '\0')
			str++;
	}
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*mset;

	str = ft_strdup(s1);
	if (!str)
		return (NULL);
	mset = ft_strdup(set);
	if (!mset)
		return (NULL);
	str = check(str, mset, 0);
	str = rev_str(str);
	if (!str)
		return (NULL);
	str = check(str, mset, 0);
	str = rev_str(str);
	if (!str)
		return (NULL);
	return ((char *) str);
} */

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	char		*trimmed;
	size_t		len;

	start = s1;
	end = s1 + ft_strlen(s1);
	while (*start && ft_strchr(set, *start))
		start++;
	while (end > start && ft_strchr(set, *(end - 1)))
		end--;
	len = end - start;
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, start, len + 1);
	return (trimmed);
}
