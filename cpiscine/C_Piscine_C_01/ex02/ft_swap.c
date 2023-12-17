/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:27:04 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/23 20:03:48 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

void	ft_swap(int *a, int *b);

void	ft_swap(int *a, int *b)
{
	int	aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

/*int	main(void)
{
	int	a;
	int	b;

	a = 5;
	b = 6;
	printf("Antes: %d %d\n", a, b);
	ft_swap(&a, &b);
	printf("Despues: %d %d\n", a, b);
	return (0);
}*/
