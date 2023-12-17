/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:49:59 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/20 23:49:17 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_bsq.h"

int	main(int argc, char **argv)
{
	struct s_getv	valof;

	if (argc < 2)
	{
		write(1, "Error. Introduce only one argument.\n", 37);
		return (1);
	}
	while (*++argv != NULL)
		if (init(*argv, 0, &valof) == 1)
			return (1);
	return (0);
}
