/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:50:06 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/29 10:50:22 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>

int	ft_str_is_alpha(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] >= 'a' && str[i] <= 'z'))
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
	char	str[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	char	c;

	c = (char) (ft_str_is_alpha(str) + 48);
	write (1, &c, 1);
	return (0);
}*/
