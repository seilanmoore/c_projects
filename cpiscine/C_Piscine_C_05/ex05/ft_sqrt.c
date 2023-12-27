/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:13:50 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/18 10:30:50 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// float	sqroot(float n)
// {
// 	float	x;
// 	float	epsilon;

// 	x = n;
// 	epsilon = 0.000001;
// 	while ((x * x - n) > epsilon)
// 		x = (x + n / x) / 2.0;
// 	return (x);
// }

// int	sqrtrecursive(int num, int guess)
// {
// 	int	newguess;

// 	newguess = guess + 1;
// 	if (newguess * newguess == num)
// 		return (newguess);
// 	else if (newguess <= (num / 2))
// 		return (sqrtrecursive(num, newguess));
// 	return (0);
// }

// int	ft_sqrt(int nb)
// {
// 	int	initialguess;

// 	if (nb < 1)
// 		return (0);
// 	initialguess = 0;
// 	return (sqrtrecursive(nb, initialguess));
// }

int	ft_sqrt(int nb)
{
	int	guess;

	guess = 1;
	if (nb < 1)
		return (0);
	while (guess <= (nb / 2) || nb == 1)
	{
		if (guess * guess == nb)
			return (guess);
		guess++;
	}
	return (0);
}

int	main(void)
{
	int	number;
	int	result;

	number = 121;
	result = ft_sqrt(number);
	if (result != 0)
		printf("Square root of %d is exactly %d.\n", number, result);
	else
		printf("Square root of %d does not exist.\n", number);
	return (0);
}

// int	main(void)
// {
// 	float	number;
// 	float	result;

// 	number = 121;
// 	result = sqroot(number);
// 	if (result != 0)
// 		printf("Square root of %f is exactly %f.\n", number, result);
// 	else
// 		printf("Square root of %f does not exist.\n", number);
// 	return (0);
// }
