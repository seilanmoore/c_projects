/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocr_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:57:48 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/10 15:57:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_bsq.h"

int	opcl_error(int fdes)
{
	if (fdes == -1)
	{
		write(1, "Error opening/closing file\n", 27);
		return (-1);
	}
	return (0);
}

int	rd_error(int bytes_read, int fdes)
{
	if (bytes_read == -1)
	{
		write(1, "Error reading file\n", 19);
		close(fdes);
		return (-1);
	}
	return (0);
}
