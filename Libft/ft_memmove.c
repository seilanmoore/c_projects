/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:10:25 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/30 17:13:41 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*s_ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr;

	ptr = dst;
	while (n-- > 0)
		*ptr++ = *(unsigned char *) src++;
	return (dst);
}

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
		s_ft_memcpy(dst, src, len);
	return (dst);
}

/* int	main(void)
{
	char	src[] = "0123456789";
	char	src1[] = "0123456789";

	printf("The prev srt is: %s.\n", src);
	ft_memmove(src, src + 3, 2);
	printf("The next srt is: %s.\n", src);
	printf("The prev srt is: %s.\n", src1);
	memmove(src1, src1 + 3, 2);
	printf("The next srt is: %s.\n", src1);
	return (0);
} */
