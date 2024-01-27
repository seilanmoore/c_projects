/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:19:03 by smoore-a          #+#    #+#             */
/*   Updated: 2024/01/23 16:50:50 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

int main(int argc, char **argv)
{
	int	nb1;
	int nb2;

	if (argc != 4)
	{
		write(1, "\n", 1);
		return (-1);
	}
	nb1 = atoi(argv[1]);
	nb2 = atoi(argv[3]);
	if (argv[2][0] == '+')
		printf("%d\n", nb1 + nb2);
	else if (argv[2][0] == '-')
		printf("%d\n", nb1 - nb2);
	else if (argv[2][0] == '/')
		printf("%d\n", nb1 / nb2);
	else if (argv[2][0] == '*')
		printf("%d\n", nb1 * nb2);
	else if (argv[2][0] == '%')
		printf("%d\n", nb1 % nb2);
	else
		write(1, "\n", 1);
	return (0);
}
