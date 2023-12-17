/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:32:19 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/05 18:25:50 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>

#include <string.h> */

char	*ft_strstr(char *str, char *to_find)
{
	int	i;

	if (*str == '\0' && *to_find == '\0')
		return (str);
	while (*str != '\0')
	{
		i = 0;
		while (str[i] == to_find[i] && to_find[i] != '\0')
		{
			i++;
		}
		if (to_find[i] == '\0')
			return (str);
		str++;
	}
	return (0);
}

/* int	main(void)
{
	char	*s1 = "Hola b";
	char	*s2 = "b";
	char	*s3 = "Hola b";
	char	*s4 = "b";
	
	s1 = ft_strstr(s1, s2);
	printf("La cadena a partir de la coincidencia es: \"%s\".\n", s1);

	s3 = strstr(s3, s4);
	printf("La cadena a partir de la coincidencia es: \"%s\".\n", s3);
	return (0);
} */
