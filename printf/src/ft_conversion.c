/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:33:58 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/19 22:31:47 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	counter(int *sum, int c)
{
	*sum += c;
}

void	ft_conversion(char format, va_list ap, int *count)
{
	if (format == 'c')
		counter(count, ft_putchar_fd(va_arg(ap, int), 1));
	else if (format == 's')
		counter(count, ft_putstr_fd(va_arg(ap, char *), 1));
	else if (format == 'p')
		counter(count, ft_hex_address((size_t)va_arg(ap, void *)));
	else if (format == 'd' || format == 'i')
		counter(count, ft_itoa(va_arg(ap, int)));
	else if (format == 'u')
		counter(count, ft_uitoa(va_arg(ap, unsigned int)));
	else if (format == 'x')
		counter(count, ft_puthex_fd(va_arg(ap, unsigned int), 0));
	else if (format == 'X')
		counter(count, ft_puthex_fd(va_arg(ap, unsigned int), 1));
	else
		counter(count, ft_putchar_fd('%', 1));
}
