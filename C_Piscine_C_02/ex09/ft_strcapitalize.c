/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:41:01 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/31 20:15:41 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strcapitalize(char *str)
{
	int	i;

	i = 0;
	if (str[i] >= 'a' && str[i] <= 'z')
		str[i] = str[i] - 32;
	i++;
	while (str[i])
	{
		if (str[i - 1] == ' ' || str[i - 1] == '-' || str[i - 1] == '+')
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] = str[i] - 32;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}

/* int	main(void)
{
	char	str[62] = "salut, ¡Omment tu vAs ? 42mOts Quarante-deux; cinquante+et+un";

	printf("%s.\n", str);
	printf("%s.\n", ft_strcapitalize(str));
} */
