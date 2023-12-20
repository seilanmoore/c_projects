/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:43:43 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/20 10:22:09 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdio.h>

char	*hex_str(int ascii, char *str)
{
	int		mod;

	mod = ascii % 16;
	if (mod > 9)
		str[1] = mod + 87;
	else
		str[1] = mod + 48;
	mod = ascii / 16;
	if (mod > 9)
		str[0] = mod + 87;
	else
		str[0] = mod + 48;
	str[2] = '\0';
	return (str);
}

void	print_str(char	*str, int i)
{
	int	j;

	j = 0;
	i -= 16;
	while (j < 16 && str[i])
	{
		if (str[i] < ' ' || str[i] > '~')
			write(1, ".", 1);
		else
			write(1, &str[i], 1);
		j++;
		i++;
		if (str[i] == '\0')
			write(1, ".", 1);
		if (j % 16 == 0 || str[i] == '\0')
			write(1, "\n", 1);
	}
}

void	print_hex(char	*str, unsigned int size)
{
	int		i;
	int		ascii;
	char	hex[2];

	i = 0;
	while (i <= size || (i % 16 != 0))
	{
		ascii = str[i];
		if (str[i] != '\0' || i == size)
		{
			write(1, &hex_str(ascii, hex)[0], 1);
			write(1, &hex_str(ascii, hex)[1], 1);
		}
		else
			write(1, "  ", 2);
		i++;
		if (i % 2 == 0)
			write(1, " ", 1);
		if (i % 16 == 0)
			print_str(str, i);
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int		i;
	int					j;
	char				*str_addr;

	i = 0;
	str_addr = addr;
	while (i < size)
	{
		j = 0;
		strcpy(str_addr, addr);
		while (str_addr[j])
		{
			write(1, &str_addr[j], 1);
			j++;
		}
		write(1, ":\n", 2);
		i++;
	}
	return (addr);
}
