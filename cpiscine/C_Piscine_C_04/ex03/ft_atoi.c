/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:13:51 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/08 09:35:48 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h> */

int	ft_atoi(char *str)
{
	int		sign;
	int		nbr;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str != '\0' && *str > 47 && *str < 58)
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	nbr *= sign;
	return (nbr);
}

/* int	main(void)
{
	printf("%d\n", ft_atoi("    \n  \t \v \f \r  ----+--+ 543 54  "));
	return (0);
} */
