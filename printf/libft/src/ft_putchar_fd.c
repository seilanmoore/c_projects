/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:47:13 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/21 15:59:33 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd(int c, int fd)
{
	unsigned char	ch;

	ch = (unsigned char) c;
	if (!fd)
		return (0);
	write(fd, &ch, 1);
	return (1);
}
