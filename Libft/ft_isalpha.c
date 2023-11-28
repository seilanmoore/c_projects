/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:42:53 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/28 14:07:28 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* #include <stdio.h>
#include <ctype.h>

#define FTCHAR '-' */

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	return (0);
}

/* int	main(void)
{
	printf("Using ft_isalpha \'%c\' returns: %d.\n",
		FTCHAR, ft_isalpha(FTCHAR));
	printf("Using isalpha \'%c\' returns: %d.\n",
		FTCHAR, isalpha(FTCHAR));
	return (0);
} */
