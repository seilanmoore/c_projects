/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:10:25 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/01 17:44:44 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;

	if ((unsigned char *) dst > (unsigned char *) src
		&& (unsigned char *) dst < (unsigned char *) src + len)
	{
		ptr_dst = (unsigned char *) dst + len;
		ptr_src = (const unsigned char *) src + len;
		while (len-- > 0)
			*(--ptr_dst) = *(--ptr_src);
	}
	else if ((unsigned char *) dst < (unsigned char *) src
		&& (unsigned char *) dst + len > (unsigned char *) src)
	{
		ptr_dst = (unsigned char *) dst;
		ptr_src = (const unsigned char *) src;
		while (len-- > 0)
			*(ptr_dst++) = *(ptr_src++);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
