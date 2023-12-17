/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:51:46 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/29 10:51:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>

int	ft_str_is_uppercase(char *str)
{
	int	i;

	i = 0;
	while (str[i] >= 'A' && str[i] <= 'Z')
	{
		i++;
	}
	if (str[i] != '\0')
		return (0);
	else
		return (1);
}

/*int	main(void)
{
	char	str[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
	char	c;

	c = (char)(ft_str_is_uppercase(str) + 48);
	write (1, &c, 1);
	return (0);
}*/
