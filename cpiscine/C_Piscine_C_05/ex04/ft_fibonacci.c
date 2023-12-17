/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:57:35 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/17 18:05:28 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define INDEX 13

int	ft_fibonacci(int index)
{
	if (index == 0)
		return (-1);
	else if (index == 1)
	{
		return (0);
	}
	else if (index == 2)
	{
		return (1);
	}
	else
		return (ft_fibonacci(index - 1) + ft_fibonacci(index - 2));
}

int	main(void)
{
	printf("The %dth index,\n"
		"of the fibonacci sequence is: %d.\n",
		INDEX, ft_fibonacci(INDEX));
}
