/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:48:24 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/01 17:10:06 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <string.h>

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	main(void)
{
	char	src[] = "This is source";
	char	dest[] = "This is ...";
	int		i = 0;

	write (1, "Old str dest: ", 15);
	write (1, &dest[0], 12);
	write (1, '\n', 1);
	strcpy(dest, src);
	write (1, "After strcpy(): ", 17);
	write (1, "After ft_strcpy(): ", 20);
	write (1, &ft_strcpy(dest, src)[0], 14);
	write (1, "\n", 1);
	return (0);
}
