/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:06:39 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/19 14:52:43 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static char	*hex_address(size_t address)
{
	size_t	len;
	char	*nbr;

	len = count_digit(address) + 3;
	nbr = (char *)malloc(len * sizeof(char));
	if (!nbr)
		return (NULL);
	nbr[--len] = '\0';
	while (len-- > 2)
	{
		if (address % 16 < 10)
			nbr[len] = '0' + (address % 16);
		else
			nbr[len] = 'a' + (address % 16) - 10;
		address /= 16;
	}
	nbr[1] = 'x';
	nbr[0] = '0';
	return (nbr);
}

void	ft_putpointer_fd(void *p, int fd)
{
	ft_putstr_fd(hex_address((size_t)p), fd);
}
