/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:52:41 by smoore-a          #+#    #+#             */
/*   Updated: 2023/11/18 11:20:10 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_bsq.h"

void	find_square(char **mtrx, int row, int col, struct s_getv *v)
{
	v->maxsize = 1;
	v->i = row - 1;
	while (v->i >= 0)
	{
		v->j = col - 1;
		while (v->j >= 0)
		{
			v->size = v->maxsize;
			v->b = 1;
			check_square(mtrx, v, row, col);
			v->j--;
		}
		v->i--;
	}
	print_result(v);
	mark_max_square(mtrx, v, 'x');
}

void	check_square(char **mtrx, struct s_getv *v, int row, int col)
{
	while (v->size <= row && v->size <= col && v->b == 1)
	{
		v->k = v->i;
		while (v->k > (v->i - v->size) && v->k >= 0
			&& v->b == 1)
		{
			v->l = v->j;
			while (v->l > (v->j - v->size) && v->l >= 0
				&& v->b == 1)
			{
				if (mtrx[v->k][v->l] == 'o')
					v->b = 0;
				else if (v->k == (v->i - v->size + 1)
					&& v->l == (v->j - v->size + 1))
					update_values(v);
				v->l--;
			}
			v->k--;
		}
		v->size++;
	}
}

void	update_values(struct s_getv *v)
{
	v->x = v->i;
	v->y = v->j;
	v->maxsize = v->size;
}

void	print_result(struct s_getv *v)
{
	printf("The row is: %d\n", v->x);
	printf("The column is: %d\n", v->y);
	printf("The size is: %d\n", v->maxsize);
}

void	mark_max_square(char **mtrx, struct s_getv *v, char fill)
{
	int	i;
	int	j;

	i = v->x;
	while (i > v->x - v->maxsize)
	{
		j = v->y;
		while (j > v->y - v->maxsize)
		{
			mtrx[i][j] = fill;
			j--;
		}
		i--;
	}
}
