/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:52:43 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/05 09:27:05 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>

#include <string.h> */

char	*ft_strcat(char *dest, char *src)
{
	char	*aux;

	aux = dest;
	while (*dest)
		dest++;
	while (*src)
		(*dest++ = *src++);
	*dest = 0;
	return (aux);
}

/* int	main(void)
{
	char	*src = "Woooorld";
	char	dest[7] = "";

	printf("La cadena original: %s\n", src);
	printf("La cadena concatenada: %s\n", ft_strcat(dest, src));
	//printf("La cadena concatenada: %s\n", strcat(dest, src));
	return (0);
} */
