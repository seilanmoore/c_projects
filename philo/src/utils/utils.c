/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:03:07 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/18 11:09:10 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	nbr;
	int	i;

	sign = 1;
	nbr = 0;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		nbr = nbr * 10 + (str[i++] - '0');
	nbr *= sign;
	return (nbr);
}

int	ft_strcmp(char *str1, char *str2)
{
	if (str1 == NULL || str2 == NULL)
		return (-1);
	while (*str1 != '\0' && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
