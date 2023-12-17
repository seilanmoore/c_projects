/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:55:29 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/17 21:47:20 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	va_list		ap_cpy;
	const char	*p;
	int			argn;

	va_start(ap, format);
	va_start(ap_cpy, format);
	p = format;
	argn = 0;
	while (*p)
	{
		if (*p != '%' || (*p == '%' && *(p + 1) == '0'))
			ft_putchar_fd(*p, 1);
		else if (ft_isdigit(*(p + 1)))
		{
			p++;
			argn = 0;
			while (p[argn] != '$')
				argn++;
			argn = ft_atoi(ft_substr(p, 0, argn));
			if (!argn)
				return (0);
			p += count_digit(argn) + 1;
			if (*p == 's')
			{
				while(argn-- > 1)
					va_arg(ap_cpy, char *);
				ft_putstr_fd(va_arg(ap_cpy, char *), 1);
			}
		}
		else if (*(p + 1) == 's')
		{
			ft_putstr_fd(va_arg(ap, char *), 1);
			p++;
		}
		p++;
		va_start(ap_cpy, format);
	}
	va_end(ap);
	va_end(ap_cpy);
	return (0);
}
