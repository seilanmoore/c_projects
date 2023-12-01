/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:28:17 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/01 17:19:38 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/* int	main(void)
{
	printf("Using ft_isprint \'%c\' returns: %d.\n",
		FTALNUM, ft_isprint(FTALNUM));
	printf("Using ft_isprint \'%c\' returns: %d.\n",
		FTALNUM, isprint(FTALNUM));
	return (0);
} */
