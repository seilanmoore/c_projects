/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:55:29 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/16 21:02:19 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printf(const char *str, ...)
{
	size_t		num_args;
	const char	*s;

	num_args = 0;
	s = str;
	while (*s)
	{
		if (*s == '%')
			num_args++;
		s++;
	}
	printf("\n%lu\n", num_args);
	return (0);
}
