/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:20:02 by smoore-a          #+#    #+#             */
/*   Updated: 2024/03/01 02:10:15 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_uitoa(unsigned int n)
{
	size_t	i;
	size_t	len;
	char	nbr[10];

	if (n == 0)
		return (put_char('0'));
	i = 0;
	while (n > 0)
	{
		nbr[i] = '0' + (n % 10);
		n /= 10;
		i++;
	}
	len = i;
	while (i-- > 0)
	{
		if (put_char(nbr[i]) == -1)
			return (-1);
	}
	return (ft_bzero(nbr, 10), len);
}
