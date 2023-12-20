/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:07:09 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/20 10:19:05 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

// #define NUM -6

int	ft_recursive_factorial(int nb)
{
	if (nb <= 1)
	{
		if (nb < 0)
			return (0);
		return (1);
	}
	else
		return (nb * ft_recursive_factorial(nb - 1));
}
