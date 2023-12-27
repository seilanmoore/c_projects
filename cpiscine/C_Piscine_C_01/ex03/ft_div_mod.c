/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:05:03 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/23 20:21:24 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

void	ft_div_mod(int a, int b, int *div, int *mod);

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	int	c;
	int	r;

	c = a / b;
	r = a % b;
	*div = c;
	*mod = r;
}

/*int	main(void)
{
	int	a;
	int	b;
	int	c;
	int	r;

	a = 50;
	b = 23;
	printf("%d %d\n", a, b);
	ft_div_mod(a, b, &c, &r);
	printf("%d %d", c, r);
	return (0);
}*/
