/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:40:52 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/19 23:24:08 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

int	ft_itoa(int n)
{
	size_t	len;
	char	*nbr;

	len = count_digit(n);
	nbr = (char *)malloc((len + 1) * sizeof(char));
	if (n == -2147483648)
		ft_strlcpy(nbr, "-2147483648", len + 1);
	else
		nbr = int_conv(nbr, 0, n, len);
	len = ft_putstr_fd(nbr, 1);
	free(nbr);
	return ((int)len);
}
