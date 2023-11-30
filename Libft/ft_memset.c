/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:31:45 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/30 18:09:40 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len-- > 0)
		*ptr++ = c;
	return (b);
}

int	main(void)
{
	char	str1[30] = "";
	char	str2[30] = "";

	printf("Using ft_memset, the string looks like this: %s.\n",
		ft_memset(str1, 'B', 5));
	printf("Using memset, the string looks like this: %s.\n",
		memset(str2, 'B', 5));
	return (0);
}
