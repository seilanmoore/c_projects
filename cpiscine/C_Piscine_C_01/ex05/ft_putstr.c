/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:32:36 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/27 12:52:39 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str);

void	ft_putstr(char *str)
{
	int		c;

	c = 0;
	while (str[c] != '\0')
	{
		write (1, str[c], 1);
		c++;
	}
}

/*int	main(void)
{
	char	c[8] = "CasoVer";

	ft_putstr(&c[0]);
	return (0);
}*/
