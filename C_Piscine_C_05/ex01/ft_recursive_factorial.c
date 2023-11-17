/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:07:09 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/15 20:41:50 by smoore-a         ###   ########.fr       */
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

// int	main(void)
// {
// 	if (ft_recursive_factorial(NUM) != 0)
// 	{
// 		printf("El factorial de %d es: %d.\n", NUM, ft_recursive_factorial(NUM));
// 	}
// 	else
// 		printf("No existe el factorial de %d.\n", NUM);
// 	return (0);
// }
