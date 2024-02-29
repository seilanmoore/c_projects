/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:58:05 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/29 23:05:18 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static size_t	count_digit(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*int_conv(char *nbr, int sign, int n, size_t len)
{
	if (!nbr)
		return (NULL);
	nbr[len] = '\0';
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	while (len-- > 0)
	{
		nbr[len] = '0' + (n % 10);
		n /= 10;
	}
	if (sign)
		nbr[0] = '-';
	return (nbr);
}

int	int_itoa(int n)
{
	size_t	len;
	char	*nbr;

	len = count_digit(n);
	nbr = (char *)malloc((len + 1) * sizeof(char));
	if (!nbr)
		return (-1);
	if (n == -2147483648)
		ft_strlcpy(nbr, "-2147483648", len + 1);
	else
		nbr = int_conv(nbr, 0, n, len);
	len = put_str(nbr, 1);
	free(nbr);
	return ((int)len);
}
