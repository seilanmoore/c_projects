/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:32:18 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/13 16:50:17 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	init_arr(char *arr, int n)
{
	arr[n] = '\0';
	while (--n >= 0)
		arr[n] = '0';
}

void	ft_putnbr(int nb, int n, int *c)
{
	int		i;
	char	num[10];

	init_arr(num, n);
	i = 0;
	while (nb > 0)
	{
		num[i++] = nb % 10 + '0';
		nb = nb / 10;
	}
	i = 0;
	n--;
	while (num[i] > num[i + 1] && i < n)
		i++;
	if (i == n)
	{
		if (*c != 0)
			write(1, ", ", 2);
		else
			*c = 1;
		while (n >= 0)
			write(1, &num[n--], 1);
	}
}

void	ft_print_combn(int n)
{
	int	exp;
	int	nb;
	int	t;
	int	c;

	c = 0;
	t = n;
	exp = 1;
	nb = 0;
	while (t > 0)
	{
		exp *= 10;
		t--;
	}
	while (nb < exp)
	{
		ft_putnbr(nb, n, &c);
		nb++;
	}
}

int	main(void)
{
	ft_print_combn(4);
	return (0);
}
