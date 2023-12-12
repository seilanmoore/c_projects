/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:16:43 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/12 12:15:08 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_items(const char *s, char c)
{
	size_t	items;

	items = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			items++;
		while (*s != c && *s)
			s++;
	}
	return (items);
}

char	**ft_split(char const *s, char c)
{
	char	**mtrx;
	size_t	i;
	size_t	item_len;

	mtrx = (char **)malloc((count_items(s, c) + 1) * sizeof(char *));
	if (!mtrx || !s)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				item_len = ft_strlen(s);
			else
				item_len = ft_strchr(s, c) - s;
			mtrx[i++] = ft_substr(s, 0, item_len);
			s += item_len;
		}
	}
	mtrx[i] = NULL;
	return (mtrx);
}
