/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:51:45 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/05 09:29:26 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>

#include <string.h> */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	dest_len;
	unsigned int	i;

	dest_len = 0;
	i = 0;
	while (dest[dest_len] != '\0')
	{
		dest_len++;
	}
	while ((i < nb) && (src[i] != '\0'))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

/*int	main(void) {
	char	dest[20] = "Hello, ";
	char*	src = "world!";
	
	ft_strncat(dest, src, 5);    
	printf("%s\n", dest);
	return (0);
}*/
