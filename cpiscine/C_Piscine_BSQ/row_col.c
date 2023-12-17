/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_col.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:58:47 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/20 13:37:05 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_bsq.h"

char	*read_line(char *fname, char *line)
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

int	frow(char *line)
{
	int		m_row;

	m_row = ft_atoi(line);
	return (m_row);
}

int	fcol(const char *fname, int i)
{
	int		fdes;
	int		bytes_read;
	int		j;
	char	buffer[1];

	fdes = open(fname, O_RDONLY);
	if (opcl_error(fdes) == -1)
		return (-1);
	bytes_read = read(fdes, buffer, sizeof(buffer));
	j = 0;
	while (bytes_read > 0 && i != 2)
	{
		if (*buffer != '\n' && i == 1)
			j++;
		if (*buffer == '\n')
			i++;
		bytes_read = read(fdes, buffer, sizeof(buffer));
	}
	if (rd_error(bytes_read, fdes) == -1)
		return (-1);
	if (opcl_error(close(fdes)) == -1)
		return (-1);
	close(fdes);
	return (j);
}
