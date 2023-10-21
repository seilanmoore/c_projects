/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_bsq.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:18:22 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/20 23:48:49 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_BSQ_H
# define LIB_BSQ_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

struct	s_getv
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	x;
	int	y;
	int	b;
	int	size;
	int	maxsize;
};

int		init(char *fname, int i, struct s_getv *valof);
int		opcl_error(int fdes);
int		rd_error(int bytes_read, int fdes);
int		frow(char *line);
int		fcol(const char *fname, int row);
char	*read_line(char *fname, char *line);
char	**crt_mtrx(char **mtrx, char *fname);
char	**read_matrix(char **mtrx, int fdes, int row, int col);
void	print_matrix(char **mtrx, int m_row, int m_col);
void	free_matrix(char **mtrx, int m_row);
int		ft_atoi(char *str);
int		ft_strlen(char *str);
char	emptyc(char *line);
char	obstaclec(char *line);
char	fillc(char *line);
// int		**create_matrix(int rows, int columns);
// void	findsq(char **mtrx, int row, int col);
void	markmaxsquare(char **mtrx, int x, int y, int size, char fill);

void	find_square(char **mtrx, int row, int col, struct s_getv *valof);
void	check_square(char **mtrx, struct s_getv *valof, int row, int col);
void	update_values(struct s_getv *valof);
void	print_result(struct s_getv *valof);
void	mark_max_square(char **mtrx, struct s_getv *valof, char mark);

#endif