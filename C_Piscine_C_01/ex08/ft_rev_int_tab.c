/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:03:36 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/27 14:35:22 by smoore-a         ###   ########.fr       */
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

void	escr(int *tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("MyArray[%d] = %d\n", i, tab[i]);
	}
}

int	main(void)
{
	int	arr[3];
	
	arr[0] = {1, 3, 4};
	int	size = sizeof(arr) / sizeof(arr[0]);

	escr(arr, size);
	ft_sort_int_tab(arr, size);
	escr (arr, size);	
	return (0);
}
