/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:00:54 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/29 11:01:02 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>

char	*ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] = str[i] + 32;
		}
		i++;
	}
	return (str);
}

/*int	main(void)
{
	char	str[] = "QWERTYUIOPASD,FGH/\\JKLZXCVBNM";
	int		i = 0;

	ft_strlowcase(str);
	while (str[i] != 0)
	{
		write(1, &str[i], 1);
		i++;
	}
	return (0);
}*/
