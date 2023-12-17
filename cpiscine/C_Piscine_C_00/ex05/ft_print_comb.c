/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:00:40 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/30 15:41:47 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	check_nb(char i, char j, char k)
{
	if (i != j && j != k && k != i)
	{
		write (1, &i, 1);
		write (1, &j, 1);
		write (1, &k, 1);
		if (i != 55)
			write (1, ", ", 2);
	}
}

void	ft_print_comb(void)
{
	char	i;
	char	j;
	char	k;

	i = 48;
	j = 48;
	k = 48;
	while (i <= 57)
	{
		j = i + 1;
		while (j <= 57)
		{
			k = j + 1;
			while (k <= 57)
			{
				check_nb(i, j, k);
				k++;
			}
			j++;
		}
		i++;
	}
}

int	main(void)
{
	ft_print_comb();
	return (0);
}
