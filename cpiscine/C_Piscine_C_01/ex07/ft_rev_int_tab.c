/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:01:20 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/27 12:15:51 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_rev_int_tab(int *tab, int size)
{
	int	temp;
	int	i;

	i = 0;
	while (i < (size / 2))
	{
		temp = tab[i];
		tab[i] = tab[size - i - 1];
		tab[size - i - 1] = temp;
		i++;
	}
}

int	main(void)
{
	int	arr[] = {1, 2, 3, 4, 5, 6 , 7, 8, 9};
	int	size = 9;
	
	for (int i = 0; i < size; i++)
	{
		printf("MyArray[%d] = %d\n", i, arr[i]);
	}
	ft_rev_int_tab(arr, size);
	for (int i = 0; i < size; i++)
	{
		printf("MyArray[%d] = %d\n", i, arr[i]);
	}	
	return (0);
}