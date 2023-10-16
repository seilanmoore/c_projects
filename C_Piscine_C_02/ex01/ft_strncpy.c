/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:49:09 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/29 10:49:14 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>

//#include <string.h>

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/*int	main(void)
{
	char	src[] = "hola";
	char	dest[] = "fdsafdsgfdas";
	int		i = 0;

	//strncpy(dest, src, 8);
	ft_strncpy(dest, src, 8);
	while ( dest[i] != '\0')
	{
		write (1, &dest[i], 1);
		i++;
	}
	return (0);
}*/
