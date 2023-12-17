/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:37:28 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/21 15:30:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_is_negative(int n);

void	ft_is_negative(int n)
{
	char	a;
	char	b;

	a = 'P';
	b = 'N';
	if (n >= 0)
	{
		write (1, &a, 1);
	}
	if (n < 0)
	{
		write (1, &b, 1);
	}
}

/*int	main(void)
{
	ft_is_negative(6);
	return (0);
}*/
