/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:25:55 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/05 09:26:09 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <unistd.h>

#include <stdio.h>

#include <string.h> */

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == '\0')
			return (0);
	return (*s1 - *(--s2));
}

/* int	main(void)
{
	char	s1[] = "Colafewf";
	char	s2[] = "colafr";
		
	printf("%d", strcmp(s1, s2));
	printf("%d", ft_strcmp(s1, s2));
	return (0);
} */
