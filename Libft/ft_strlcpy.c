/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:50:37 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/30 13:09:19 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/* unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (i >= size - 1)
		dest[size - 1] = '\0';
	else
		dest[i] = '\0';
	return (i);
} */

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (dstsize != 0)
			dst[i] = src[i];
		i++;
	}
	if (i >= dstsize - 1)
		dst[dstsize - 1] = '\0';
	else
		dst[i] = '\0';
	return (i);
}

int	main(void)
{
	char	*src1 = "aaa";
	char	dst1[0] = "";
	char	*src2 = "aaa";
	char	dst2[0] = "";

	/* ft_strlcpy(dst1, src1, 0);
	printf("Using ft_strlcpy, the string looks like this: %s. "
		"And the size of the src is : %lu.\n", dst1, ft_strlcpy(dst1, src1, 0));
	strlcpy(dst2, src2, 0); */
	printf("Using strlcpy, the string looks like this: %s. "
		"Size of the src is : %lu.\n",
		dst2, strlcpy(dst2, src2, 0));
	return (0);
}
