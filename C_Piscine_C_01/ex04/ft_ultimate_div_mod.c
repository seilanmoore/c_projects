/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:19:29 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/23 20:31:17 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

void	ft_ultimate_div_mod(int *a, int *b);

void	ft_ultimate_div_mod(int *a, int *b)
{
	int	c;
	int	r;

	c = *a;
	r = *b;
	*a = c / r;
	*b = c % r;
}

/*int	main(void)
{
	int	a;
	int	b;

	a = 10;
	b = 2;
	printf("%d %d\n", a, b);
	ft_ultimate_div_mod(&a, &b);
	printf("%d %d", a, b);
	return (0);
}*/
