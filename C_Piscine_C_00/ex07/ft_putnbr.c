/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:30:56 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/12 20:54:34 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int nb)
{
	int		i;
	char	num[10];

	*num = '\0';
	i = 0;
	if (nb == -2147483648)
		write(1, "-2147483648", 11);
	if (nb == 0)
		write (1, "0", 1);
	if (nb < 0 && nb != -2147483648)
	{
		write (1, "-", 1);
		nb = -nb;
	}
	while (nb > 0)
	{
		num[i++] = nb % 10 + '0';
		nb = nb / 10;
	}
	while (--i >= 0)
		write(1, &num[i], 1);
}

/* int	main(void)
{
	int	nb = 0000;

	ft_putnbr(nb);
	return (0);
} */
