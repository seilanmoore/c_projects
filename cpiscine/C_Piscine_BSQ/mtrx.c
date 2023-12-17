/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:00:15 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/20 20:19:29 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_bsq.h"

char	**crt_mtrx(char **mtrx, char *fname)
{
	int		fdes;

	fdes = open(fname, O_RDONLY);
	mtrx = read_matrix(mtrx, fdes, 0, 0);
	close(fdes);
	return (mtrx);
}

char	**read_matrix(char **mtrx, int fdes, int row, int col)
{
	char	buffer[1];
	int		bytes_read;

	bytes_read = read(fdes, buffer, sizeof(buffer));
	while (*buffer != '\n')
		bytes_read = read(fdes, buffer, sizeof(buffer));
	bytes_read = read(fdes, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		if (*buffer != '\n')
		{
			mtrx[row][col] = *buffer;
			col++;
		}
		else
		{
			col = 0;
			row++;
		}
		bytes_read = read(fdes, buffer, sizeof(buffer));
	}
	return (mtrx);
}

void	print_matrix(char **mtrx, int m_row, int m_col)
{
	int	i;
	int	j;

	i = 0;
	while (i < m_row)
	{
		j = 0;
		while (j < m_col)
			write(1, &mtrx[i][j++], 1);
		write(1, "\n", 1);
		i++;
	}
}

void	free_matrix(char **mtrx, int m_row)
{
	int	i;

	i = 0;
	while (i < m_row)
		free(mtrx[i++]);
	free(mtrx);
}
