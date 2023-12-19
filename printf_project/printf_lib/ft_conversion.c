/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:33:58 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/19 09:20:14 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_conversion(char format, va_list ap)
{
	if (format == 'c')
		ft_putchar_fd(*va_arg(ap, char *), 1);
	else if (format == 's')
		ft_putstr_fd(va_arg(ap, char *), 1);
	else if (format == 'p')
		ft_putpointer_fd(va_arg(ap, void *), 1);
}

/* 	else if (format == 'p')
		
	else if (format == 'd')

	else if (format == 'i')

	else if (format == 'u')

	else if (format == 'x')

	else if (format == 'X')

	else if (format == '%') */