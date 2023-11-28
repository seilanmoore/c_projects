/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isacii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:31:18 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/28 16:26:23 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* #include <stdio.h>
#include <ctype.h>

#define FTALNUM 128 */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/* int	main(void)
{
	printf("Using ft_isascii \'%c\' returns: %d.\n",
		FTALNUM, ft_isascii(FTALNUM));
	printf("Using ft_isascii \'%c\' returns: %d.\n",
		FTALNUM, isascii(FTALNUM));
	return (0);
} */
