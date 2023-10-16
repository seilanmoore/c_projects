/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 12:35:46 by smoore-a          #+#    #+#             */
/*   Updated: 2023/09/30 20:37:47 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

void	ft_strcpy(char *dest, char *src);

int		*ft_strlen(char *str);

void	ft_putstr(char *str);

int	main(int argc, char **argv)
{
	char	*str;
	
	str = (char *)malloc((unsigned long)ft_strlen(argv[1]));
	if (argc > 1 && str != NULL)
	{
		ft_strcpy(str, argv[1]);
		ft_putstr(str);
		free(str);
	}
	else
		ft_putstr("Error");
	return (0);
}
