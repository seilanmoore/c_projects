/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:33:58 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/19 14:52:22 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_conversion(char format, va_list ap)
{
	if (format == 'c')
		ft_putchar_fd(*va_arg(ap, char *), 1);
	else if (format == 's')
		ft_putstr_fd(va_arg(ap, char *), 1);
	else if (format == 'p')
		ft_putpointer_fd(va_arg(ap, void *), 1);
	else if (format == 'd' || format == 'i')
		ft_putstr_fd(ft_itoa(va_arg(ap, int)), 1);
	else if (format == 'u')
		ft_putstr_fd(ft_uitoa(va_arg(ap, unsigned int)), 1);
	else if (format == 'x')
		ft_puthex_fd(va_arg(ap, unsigned int), 0);
	else if (format == 'X')
		ft_puthex_fd(va_arg(ap, unsigned int), 1);
	else
		ft_putchar_fd('%', 1);
}
