/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:50:44 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/29 10:50:51 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>

int	ft_str_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
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
	char	str[] = "1234567890";
	char	c;

	c = (char)(ft_str_is_numeric(str) + 48);
	write (1, &c, 1);
	return (0);
}*/
