/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:47:46 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/01 17:18:27 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr;

	ptr = dst;
	while (n-- > 0 && (dst != NULL || src != NULL))
		*ptr++ = *(unsigned char *) src++;
	return (dst);
}

/* int	main(void)
{
	char	src1[30] = "Hello my name ";
	char	dst1[30] = "Is Manolo.";
	char	src2[30] = "Hello my name ";
	char	dst2[30] = "Is Manolo.";

	printf("Using ft_memcpy, the string looks like this: %s.\n",
		ft_memcpy(dst1, src1, 10));
	printf("Using memcpy, the string looks like this: %s.\n",
		memcpy(dst2, src2, 10));
	return (0);
} */
