/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:13:47 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/02 14:41:33 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//size es el tamaño del buffer
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
