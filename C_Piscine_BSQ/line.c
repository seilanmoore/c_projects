/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:56:26 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/12 12:56:22 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_bsq.h"

char	emptyc(char *line)
{
	int		i;

	i = ft_strlen(line) - 3;
	if (line[i] > 31 && line[i] < 127)
		return (line[i]);
	write(1, "Error: parsing empty character.\n", 33);
	return (1);
}

char	obstaclec(char *line)
{
	int		i;

	i = ft_strlen(line) - 2;
	if (line[i] > 31 && line[i] < 127)
		return (line[i]);
	write(1, "Error: parsing obstacle character.\n", 36);
	return (1);
}

char	fillc(char *line)
{
	int		i;

	i = ft_strlen(line) - 1;
	if (line[i] > 31 && line[i] < 127)
		return (line[i]);
	write(1, "Error: parsing fill character.\n", 32);
	return (1);
}
