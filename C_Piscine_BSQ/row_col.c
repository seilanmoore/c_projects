/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_col.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:58:47 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/12 12:56:07 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_bsq.h"

char	*read_line(char *line, char *fname)
{
	int		fdes;
	char	buffer[1];
	int		bytes_read;
	int		i;

	i = 0;
	fdes = open(fname, O_RDONLY);
	bytes_read = read(fdes, buffer, sizeof(buffer));
	while (*buffer != '\n' && bytes_read > 0)
	{
		line[i++] = *buffer;
		bytes_read = read(fdes, buffer, sizeof(buffer));
	}
	line[i] = '\0';
	bytes_read = read(fdes, buffer, sizeof(buffer));
	close(fdes);
	return (line);
}

int	frow(char *line, char *fname)
{
	int		m_row;

	m_row = ft_atoi(read_line(line, fname));
	return (m_row);
}

int	fcol(const char *fname, int row)
{
	int		fdes;
	int		bytes_read;
	int		col;
	char	buffer[1];

	fdes = open(fname, O_RDONLY);
	if (opcl_error(fdes) == -1)
		return (-1);
	bytes_read = read(fdes, buffer, sizeof(buffer));
	col = 0;
	while (bytes_read > 0 && row != 3)
	{
		if (*buffer != '\n' && row == 2)
			col++;
		if (*buffer == '\n')
			row++;
		bytes_read = read(fdes, buffer, sizeof(buffer));
	}
	if (rd_error(bytes_read, fdes) == -1)
		return (-1);
	if (opcl_error(close(fdes)) == -1)
		return (-1);
	close(fdes);
	return (col);
}
