/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:37:04 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/27 22:16:30 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static size_t	count_digit(unsigned int n)
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

int	ft_puthex_fd(unsigned int n, int low_upper)
{
	size_t	len;
	char	*nbr;

	len = count_digit(n);
	nbr = (char *)malloc((len + 1) * sizeof(char));
	if (!nbr)
	{
		free(nbr);
		return (0);
	}
	nbr[len] = '\0';
	while (len-- > 0)
	{
		if (n % 16 < 10)
			nbr[len] = '0' + (n % 16);
		else if (!low_upper)
			nbr[len] = 'a' + (n % 16) - 10;
		else if (low_upper)
			nbr[len] = 'A' + (n % 16) - 10;
		n /= 16;
	}
	len = ft_strlen(nbr);
	put_str(nbr, 1);
	free(nbr);
	return (len);
}
