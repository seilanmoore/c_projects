/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:45:41 by smoore-a          #+#    #+#             */
/*   Updated: 2024/01/23 19:59:41 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

static int ft_atoi(char *nb)
{
	int num;
	int i;

	num = 0;
	i = 0;
	if (*nb < '0' || *nb > '9')
		return (-1);
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		num *= 10;
		num += nb[i] - '0';
		i++;
	}
	return (num);
}

static char *dtoh(char *str, int nb)
{
	char 	*dig = "0123456789abcdef";
	char	hex[100];
	int 	i = 0;
	int		j = 0;

	while (nb > 0)
	{
		hex[i++] = dig[nb % 16];
		nb /= 16;
	}
	while (--i >= 0)
	{
		str[j++] = hex[i];
	}
	str[j] = '\0';
	return (str);
}

int main(int argc, char **argv)
{
	int nb;
	char *hexnb;

	if (argc != 2)
	{
		write(1, "\n", 1);
		return (-1);
	}
	nb = ft_atoi(argv[1]);
	if(nb == -1)
	{
		write(1, "\n", 1);
		return (-1);
	}
	hexnb = dtoh(hexnb, nb);
	while (*hexnb)
	{
		write(1, &(*hexnb), 1);
		hexnb++;
	}
	write(1, "\n", 1);
	return (0);
}
