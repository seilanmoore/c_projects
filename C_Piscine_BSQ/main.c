/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:49:59 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/12 16:09:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_bsq.h"

int	main(int argc, char **argv)
{
	char	*fname;
	char	*line;
	char	**mtrx;
	int		m_row;
	int		m_col;
	int		i;

	if (argc < 2)
	{
		write(1, "Error. Introduce only one argument.\n", 37);
		return (1);
	}
	while (*++argv != NULL)
	{
		fname = *argv;
		m_col = fcol(fname, 0);
		line = (char *)malloc(m_col * sizeof(char));
		m_row = frow(line, fname);
		mtrx = (char **)malloc(m_row * sizeof(char *));
		i = 0;
		while (i < m_row)
			mtrx[i++] = (char *)malloc(m_col * sizeof(char));
		if (mtrx == NULL)
		{
			write(1, "Error: Memory allocation failed.\n", 33);
			return (1);
		}
		line = read_line(line, fname);
		mtrx = crt_mtrx(mtrx, fname);
		createsqmtrx(mtrx, m_row, m_col, line);
		print_matrix(mtrx, m_row, m_col);
		free(line);
		free_matrix(mtrx, m_row);
	}
	return (0);
}
