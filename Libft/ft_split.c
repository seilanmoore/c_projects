/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:16:43 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/11 17:51:05 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_items(const char *s, char c)
{
	size_t	i;
	size_t	items;

	i = 0;
	items = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
			i++;
		if (i && s[i - 1] != c)
			items++;
	}
	return (items);
}

static char	*extract_substring(char *str, char c)
{
	size_t	len;

	len = 0;
	while (*str && *str == c)
		str++;
	while (str[len] && str[len] != c)
		len++;
	return (ft_substr(str, 0, len));
}

static char	**allocate_mem(char **mtrx, char *s, char c)
{
	char	*str;
	size_t	i;
	size_t	items;

	i = 0;
	str = s;
	items = count_items(str, c);
	while (items-- > 0)
	{
		mtrx[i] = extract_substring(str, c);
		if (!mtrx[i])
		{
			while (i > 0)
				free(mtrx[--i]);
			free(mtrx);
			return (NULL);
		}
		str += ft_strlen(mtrx[i]);
		while (*str == c)
			str++;
		i++;
	}
	mtrx[i] = NULL;
	return (mtrx);
}

/* static char	**allocate_mem(char **mtrx, char *s, char c)
{
	size_t	i;
	size_t	len;
	char	*str;
	size_t	items;

	i = 0;
	len = 0;
	str = s;
	items = count_items(str, c);
	while (items-- > 0)
	{
		while (*str && *str == c)
			str++;
		len = 0;
		while (str[len] && str[len] != c)
			len++;
		mtrx[i] = ft_substr(str, 0, len);
		if (!mtrx[i])
			return (NULL);
		i++;
		str += len;
	}
	mtrx[i] = NULL;
	return (mtrx);
} */

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**mtrx;
	char	**temp;

	str = (char *) s;
	mtrx = (char **)malloc((count_items(str, c) + 1) * sizeof(char *));
	if (!mtrx)
		return (NULL);
	temp = allocate_mem(mtrx, str, c);
	if (!temp)
	{
		free(mtrx);
		return (NULL);
	}
	return (temp);
}
