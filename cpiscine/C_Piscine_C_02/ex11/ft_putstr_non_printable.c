/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 07:35:57 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/01 08:52:41 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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

void	ft_putstr_non_printable(char *str)
{
	int		i;
	int		ascii;
	char	hex[2];

	i = 0;
	while (str[i])
	{
		if (str[i] < ' ' || str[i] > '~')
		{
			ascii = str[i];
			write(1, "\\", 1);
			write(1, &hex_str(ascii, hex)[0], 1);
			write(1, &hex_str(ascii, hex)[1], 1);
		}
		else
			write(1, &str[i], 1);
		i++;
	}
}

// int	main(void)
// {
// 	char	*str = "Coucou\ntu \033vas\037 bien\177 ?";

// 	ft_putstr_non_printable(str);
// }
