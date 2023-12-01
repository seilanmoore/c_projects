/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:50:37 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/01 17:21:54 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize > 0)
	{
		i = 0;
		while (i < src_len && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

/* int	main(void)
{
	char	*src1;
	char	dst1[0] = "";
	char	*src2;
	char	dst2[0] = "";

	src1 = "aaa";
	src2 = "aaa";
	ft_strlcpy(dst1, src1, 0);
	printf("Using ft_strlcpy, the string looks like this: %s. "
		"And the size of the src is : %lu.\n", dst1, ft_strlcpy(dst1, src1, 0));
	strlcpy(dst2, src2, 0);
	printf("Using strlcpy, the string looks like this: %s. "
			"Size of the src is : %lu.\n",
			dst2,
			strlcpy(dst2, src2, 0));
	return (0);
} */
