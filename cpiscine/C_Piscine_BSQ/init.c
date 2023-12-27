/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:45:08 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/20 23:39:16 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_bsq.h"

int	init(char *fname, int i, struct s_getv *valof)
{
	char	*line;
	char	**mtrx;

	line = (char *)malloc(fcol(fname, 0) * sizeof(char));
	line = read_line(fname, line);
	mtrx = (char **)malloc(frow(line) * sizeof(char *));
	while (i < frow(line))
		mtrx[i++] = (char *)malloc(fcol(fname, 0) * sizeof(char));
	if (mtrx == NULL)
	{
		write(1, "Error: Memory allocation failed.\n", 33);
		return (1);
	}
	mtrx = crt_mtrx(mtrx, fname);
	printf("Rows: %d\n", frow(line));
	printf("Columns: %d\n", fcol(fname, 0));
	find_square(mtrx, frow(line), fcol(fname, 0), valof);
	print_matrix(mtrx, frow(line), fcol(fname, 0));
	free_matrix(mtrx, frow(line));
	free(line);
	return (0);
}
