/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:52:41 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/12 12:55:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_bsq.h"

void	createsqmtrx(char **mtrx, int rows, int cols, char *line)
{
	int	msize;
	int	x;
	int	y;
	int	**dp;
	int	i;
	int	j;
	int	minvalue;

	dp = (int **)malloc(rows * sizeof(int *));
	i = 0;
	while (i < rows)
	{
		dp[i] = (int *)malloc(cols * sizeof(int));
		i++;
	}
	msize = 0;
	x = 0;
	y = 0;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (mtrx[i][j] == obstaclec(line))
			{
				dp[i][j] = 0;
			}
			else
			{
				dp[i][j] = 1;
				if (i > 0 && j > 0)
				{
					minvalue = dp[i - 1][j - 1];
					if (dp[i - 1][j] < minvalue)
					{
						minvalue = dp[i - 1][j];
					}
					if (dp[i][j - 1] < minvalue)
					{
						minvalue = dp[i][j - 1];
					}
					dp[i][j] += minvalue;
				}
				if (dp[i][j] > msize)
				{
					msize = dp[i][j];
					x = i - msize + 1;
					y = j - msize + 1;
				}
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < rows)
	{
		free(dp[i]);
		i++;
	}
	free(dp);
	markmaxsquare(mtrx, x, y, msize, fillc(line));
}

void	markmaxsquare(char **mtrx, int x, int y, int size, char fill)
{
	int	i;
	int	j;

	i = x;
	while (i < x + size)
	{
		j = y;
		while (j < y + size)
		{
			mtrx[i][j] = fill;
			j++;
		}
		i++;
	}
}
