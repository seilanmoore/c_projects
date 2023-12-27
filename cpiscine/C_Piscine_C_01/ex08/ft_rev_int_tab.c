/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:03:36 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/20 10:20:07 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] > tab[j])
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/* int	main(void)
{
	int	arr[] = {1, 3, 4, 0, 2, 8, 2, 5, 3, 9, 7, 0, 12};
	int	size = sizeof(arr) / sizeof(arr);

	escr(arr, 13);
	ft_sort_int_tab(arr, 13);
	escr (arr, 13);	
	return (0);
} */
