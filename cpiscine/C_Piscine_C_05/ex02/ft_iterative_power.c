/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:42:37 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/15 22:55:37 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

// #define NUM 5
// #define POWER 3

int	ft_iterative_power(int nb, int power)
{
	int	aux;

	aux = nb;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	else
	{
		while (power != 1)
		{
			aux *= nb;
			power--;
		}
	}
	return (aux);
}

// int	main(void)
// {
// 	printf("The %dth power of %d is: %d.\n", POWER, NUM, ft_iterative_power(NUM, POWER));
// }
