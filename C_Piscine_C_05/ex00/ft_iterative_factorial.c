/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:14:57 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/17 14:49:39 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#define MIN -2147483648
#define MAX 2147483647
#define NB -5

int	ft_iterative_factorial(int nb)
{
	int	res;

	res = nb;
	if (nb <= 0 || nb > MAX)
	{
		if (nb < 0 || nb > MAX)
			write(1, "Error. Valor inválido.", 24);
		return (1);
	}
	else
	{
		while (--nb > 0)
			res *= nb;
		return (res);
	}
}

int	main(void)
{
	int	a = 0;

	if (a == 0)
		return (2);
	printf("El factorial de %d es: %d.\n", NB, ft_iterative_factorial(NB));
	return (0);
}
