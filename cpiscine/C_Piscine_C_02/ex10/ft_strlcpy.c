/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:16:42 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/02 13:46:13 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
// #include <bsd/string.h>
////cc -Wall -Wextra ft_strlcpy.c -lbsd.
////Para compilar incluyendo esta biblioteca.

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
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
}

// int	main(void)
// {
// 	char	*src = "Loqueseabro";
// 	char	dest[8] = "";
// 	char	*src1 = "Loqueseabro";
// 	char	dest1[8] = "";

// 	strlcpy(dest, src, 5);
// 	printf("strlcpy: %s\n", dest);
// 	ft_strlcpy(dest1, src1, 5);
// 	printf("ft_strlcpy: %s\n", dest1);
// 	return (0);
// }
