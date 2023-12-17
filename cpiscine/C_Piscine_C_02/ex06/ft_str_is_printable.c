/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:52:11 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/29 10:52:15 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>

int	ft_str_is_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i] >= ' ' && str[i] <= '~')
	{
		i++;
	}
	if (str[i] != '\0')
		return (0);
	else
		return (1);
}

/*int	main(void)
{
	char	str[] = "\"+45 \"\"i\\%&2";
	char	c;

	c = (char)(ft_str_is_printable(str) + 48);
	write (1, &c, 1);
	return (0);
}*/
