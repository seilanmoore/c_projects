/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:33:43 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/01 17:16:25 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/* int	main(void)
{
	printf("Using ft_isalnum \'%c\' returns: %d.\n",
		FTALNUM, ft_isalnum(FTALNUM));
	printf("Using ft_isalnum \'%c\' returns: %d.\n",
		FTALNUM, isalnum(FTALNUM));
	return (0);
} */
