/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:57:00 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/01 17:17:29 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/* int	main(void)
{
	char	*str = "fefefefe";

	printf("Using ft_strlen, the lengnth is: %lu.\n", ft_strlen(str));
	printf("Using strlen, the lengnth is: %lu.\n", strlen(str));
	return (0);
} */
