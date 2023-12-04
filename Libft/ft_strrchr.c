/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:04:38 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/04 17:22:19 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char		*str;
	unsigned char		*pos;
	unsigned char		ch;

	ch = (unsigned char)c;
	if (ch == '\0' && *s == '\0')
		return ((char *)s);
	str = (unsigned char *)s;
	pos = NULL;
	while (*str != '\0')
	{
		if (*str == ch)
			pos = str;
		str++;
	}
	if (pos != NULL)
		return ((char *)pos);
	if (ch == 0)
		return ((char *)str);
	return (NULL);
}
