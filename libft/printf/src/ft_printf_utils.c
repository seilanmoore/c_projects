/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:56:57 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/29 23:05:18 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	put_str(char *s, int fd)
{
	if (!fd)
		return (0);
	if (!s)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	write(fd, s, ft_strlen(s));
	return (ft_strlen(s));
}

int	put_char(int c, int fd)
{
	unsigned char	ch;

	ch = (unsigned char) c;
	if (!fd)
		return (0);
	write(fd, &ch, 1);
	return (1);
}
