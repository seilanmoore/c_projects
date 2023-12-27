/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:20:02 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/21 16:25:31 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	count_digit(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_uitoa(unsigned int n)
{
	size_t	len;
	char	*nbr;

	len = count_digit(n);
	nbr = (char *)malloc((len + 1) * sizeof(char));
	if (!nbr)
	{
		free(nbr);
		return (-1);
	}
	nbr[len] = '\0';
	while (len-- > 0)
	{
		nbr[len] = '0' + (n % 10);
		n /= 10;
	}
	ft_putstr_fd(nbr, 1);
	len = ft_strlen(nbr);
	free(nbr);
	return (len);
}
