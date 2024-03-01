/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:58:05 by smoore-a          #+#    #+#             */
/*   Updated: 2024/03/01 01:32:12 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	int_conv(int n, int len)
{
	char	nbr[10];
	int		i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		if (write(1, "-", 1) == -1)
			return (-1);
	}
	while (n > 0)
	{
		nbr[i] = '0' + (n % 10);
		n /= 10;
		i++;
	}
	len += i;
	while (i-- > 0)
	{
		if (write(1, &nbr[i], 1) == -1)
			return (-1);
	}
	return (len);
}

int	int_itoa(int n)
{
	if (n == 0)
		return (write(1, "0", 1));
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
		return (int_conv(n, 1));
	return (int_conv(n, 0));
}
