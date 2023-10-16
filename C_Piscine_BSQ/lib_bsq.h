/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_bsq.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:18:22 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/12 12:22:02 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_BSQ_H
# define LIB_BSQ_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

int		opcl_error(int fdes);
int		rd_error(int bytes_read, int fdes);
int		frow(char *line, char *fname);
int		fcol(const char *fname, int row);
char	*read_line(char *line, char *fname);
char	**crt_mtrx(char **mtrx, char *fname);
char	**read_matrix(char **mtrx, int fdes);
void	print_matrix(char **mtrx, int m_row, int m_col);
void	free_matrix(char **mtrx, int m_row);
int		ft_atoi(char *str);
int		ft_strlen(char *str);
char	emptyc(char *line);
char	obstaclec(char *line);
char	fillc(char *line);
int		**create_matrix(int rows, int columns);
void	createsqmtrx(char **mtrx, int rows, int cols, char *line);
void	markmaxsquare(char **mtrx, int x, int y, int size, char fill);

#endif