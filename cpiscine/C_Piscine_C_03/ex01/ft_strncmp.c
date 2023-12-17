/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:52:25 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/05 09:26:29 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <unistd.h>

#include <stdio.h>

#include <string.h> */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	if (n == 0)
		return (0);
	n++;
	while (--n != 0)
	{
		if (*s1 != *s2++)
			return (*s1 - *(--s2));
		if (*s1++ == 0)
			break ;
	}
	return (0);
}

/* int	main(void)
{
	char	*s1 = "Chahb";
	char	*s2 = "Chahb";
		
	printf("%d\n", strncmp(s1, s2, 10));
	printf("%d\n", ft_strncmp(s1, s2, 10));
	return (0);
} */
