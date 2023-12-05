/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:14:57 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/05 15:50:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_needle(char *pos, char *str2, size_t len, size_t j)
{
	size_t	i;

	i = 0;
	while (*pos == str2[i] && *pos != '\0' && str2[i] && j < len)
	{
		pos++;
		i++;
		j++;
	}
	if (str2[i] == '\0')
		return (0);
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned char	*pos;
	size_t			i;
	size_t			j;

	str2 = (unsigned char *)needle;
	str1 = (unsigned char *)haystack;
	i = 0;
	j = 0;
	if (*str2 == '\0')
		return ((char *)str1);
	if (*str1 != '\0')
	{
		while (*str1 != '\0' && i < len)
		{
			pos = str1;
			if (find_needle((char *)pos, (char *)str2, len, i) == 0)
				return ((char *)str1);
			str1++;
			i++;
		}
	}
	return (0);
}
