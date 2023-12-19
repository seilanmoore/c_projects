/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:33:46 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/04 16:53:27 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned const char	*str;
	unsigned char		ch;

	ch = (unsigned char)c;
	if (ch == '\0' && *s == '\0')
		return ((char *)s);
	str = (unsigned const char *)s;
	while (*str != '\0')
	{
		if (*str == ch)
			return ((char *)str);
		str++;
	}
	if (ch == 0)
		return ((char *)str);
	return (NULL);
}
