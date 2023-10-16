/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:00:15 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/12 12:56:03 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_bsq.h"

char	**crt_mtrx(char **mtrx, char *fname)
{
	int		fdes;
	char	buffer[1];
	int		bytes_read;

	fdes = open(fname, O_RDONLY);
	bytes_read = read(fdes, buffer, sizeof(buffer));
	mtrx = read_matrix(mtrx, fdes);
	close(fdes);
	return (mtrx);
}

int	**create_matrix(int rows, int columns)
{
	int	**matrix;
	int	i;
	int	j;

	i = 0;
	matrix = (int **)malloc(rows * sizeof(int *));
	while (i < rows)
	{
		matrix[i] = (int *)malloc(columns * sizeof(int));
		i++;
	}
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < columns)
		{
			matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	return (matrix);
}

char	**read_matrix(char **mtrx, int fdes)
{
	char	buffer[1];
	int		bytes_read;
	int		row;
	int		col;

	row = 0;
	col = 0;
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
