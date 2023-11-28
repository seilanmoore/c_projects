/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:27:38 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/28 14:43:36 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* #include <stdio.h>
#include <ctype.h>

#define FTDIGIT 'a' */

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

/* int	main(void)
{
	printf("Using ft_isdigit \'%c\' returns: %d.\n",
		FTDIGIT, ft_isdigit(FTDIGIT));
	printf("Using isdigit \'%c\' returns: %d.\n",
		FTDIGIT, isdigit(FTDIGIT));
	return (0);
} */
