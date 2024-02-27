/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_address.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:06:39 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/27 22:16:18 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static size_t	count_digit(size_t n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		len++;
	while (n != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

static void	hex_conv(char *nbr, size_t address, size_t len)
{
	while (len-- > 2)
	{
		if (address % 16 < 10)
			nbr[len] = '0' + (address % 16);
		else
			nbr[len] = 'a' + (address % 16) - 10;
		address /= 16;
	}
}

int	ft_hex_address(size_t address)
{
	size_t	len;
	char	*nbr;

	if (!address)
	{
		put_str("(nil)", 1);
		return (5);
	}
	len = count_digit(address) + 3;
	nbr = (char *)malloc(len * sizeof(char));
	if (!nbr)
	{
		free(nbr);
		return (0);
	}
	nbr[--len] = '\0';
	hex_conv(nbr, address, len);
	nbr[1] = 'x';
	nbr[0] = '0';
	len = put_str(nbr, 1);
	free(nbr);
	return ((int)len);
}
