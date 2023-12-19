/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:08:02 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/19 09:15:24 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_lib/libftprintf.h"

int	main(void)
{
	char p[] = "Adios.";

	ft_printf("Hola %p %s %s %s thrsht %s %s %s %s %s %s.\n", p, "B", "C", "D", "F", "G", "H", "I", "J", "K");
	printf("Hola %p %s %s %s thrsht %s %s %s %s %s %s.\n", p, "B", "C", "D", "F", "G", "H", "I", "J", "K");
	return (0);
}
