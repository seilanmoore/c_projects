/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_address.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:06:39 by smoore-a          #+#    #+#             */
/*   Updated: 2024/03/01 01:53:18 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	hex_conv(size_t n)
{
	size_t	i;
	size_t	len;
	char	nbr[16];

	i = 0;
	while (n > 0)
	{
		if (n % 16 < 10)
			nbr[i] = '0' + (n % 16);
		else
			nbr[i] = 'a' + (n % 16) - 10;
		n /= 16;
		i++;
	}
	len = i;
	while (i-- > 0)
	{
		if (ft_putchar_fd(nbr[i], 1) == -1)
			return (-1);
	}
	return (ft_bzero(nbr, 16), len);
}

int	ft_hex_address(size_t address)
{
	int		len;

	if (!address)
	{
		put_str("0x0", 1);
		return (3);
	}
	if (write(1, "0x", 2) == -1)
		return (-1);
	len = 2;
	len += hex_conv(address);
	return (len);
}
