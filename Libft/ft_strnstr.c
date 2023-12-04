/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:14:57 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/04 23:54:12 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			j;
	int				i;

	j = len;
	str1 = (unsigned char *)big;
	str2 = (unsigned char *)little;
	if (*str1)
	{
		if (*str2 == '\0')
			return ((char *)str1);
		while (len-- > 0)
		{
			i = 0;
			while (str1[i] == str2[i] && str2[i] != '\0')
				i++;
			if (str2[i] == '\0')
				return ((char *)str1);
			str1++;
		}
	}
	return (0);
}
