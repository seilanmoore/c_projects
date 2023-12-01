/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:12:28 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/01 17:20:02 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset (s, 0, n);
}

/* int	main(void)
{
	char	str1[30];
	char	str2[30];

	ft_bzero(str1, 5);
	printf("Using ft_bzero, the string looks like this: %s.\n", str1);
	bzero(str2, 5);
	printf("Using bzero, the string looks like this: %s.\n", str2);
	return (0);
} */
