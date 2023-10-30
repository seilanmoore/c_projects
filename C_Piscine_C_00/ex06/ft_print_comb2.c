/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 07:21:20 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/30 08:47:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	check_nb(char i, char j, char k, char l)
{
	if ((i * 10) + j < (k * 10) + l)
	{
		if (((i * 10) + j + (k * 10) + l) != 2 * ((48 * 10) + 48) + 1)
			write (1, ", ", 2);
		write (1, &i, 1);
		write (1, &j, 1);
		write (1, " ", 1);
		write (1, &k, 1);
		write (1, &l, 1);
	}
}

void	ft_print_comb2(void)
{
	char	i;
	char	j;
	char	k;
	char	l;

	i = 48;
	while (i <= 57)
	{
		j = 48;
		while (j <= 57)
		{
			k = 48;
			while (k <= 57)
			{
				l = 48;
				while (l <= 57)
				{
					check_nb(i, j, k, l);
					l++;
				}
				k++;
			}
			j++;
		}
		i++;
	}
}

int	main(void)
{
	ft_print_comb2();
	return (0);
}
