/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:50:40 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/23 20:12:42 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(void)
{
	char	a[25] = "Hola";
	char	*b = " yo manolo\n";

	strlcat(a, b, 25);
	ft_printf("Result: %s", a);
	return (0);
}
