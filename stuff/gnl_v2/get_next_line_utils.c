/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:33:58 by smoore-a          #+#    #+#             */
/*   Updated: 2024/01/01 22:15:14 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	found_nl(char *cache)
{
	int	i;

	if (cache)
	{
		i = 0;
		while (cache[i] && cache[i] != '\n')
			i++;
		if (cache[i] == '\n')
			return (i);
		return (-1);
	}
	return (-2);
}

char	*create_cache(char *cache, char *buffer)
{
	size_t	final_size;
	int		i;

	final_size = ft_strlen(buffer) + 1;
	cache = (char *)malloc(final_size * sizeof(char));
	if (!cache)
		return (NULL);
	i = -1;
	while (buffer[++i])
		cache[i] = buffer[i];
	cache[i] = '\0';
	return (cache);
}

char	*extend_cache(char *cache, char *buffer)
{
	size_t	final_size;
	size_t	i;
	size_t	j;
	char	*temp;

	temp = NULL;
	if (!cache)
		return (create_cache(cache, buffer));
	final_size = ft_strlen(cache) + ft_strlen(buffer) + 1;
	temp = (char *)malloc(final_size * sizeof(char));
	if (!temp)
	{
		free(cache);
		return (NULL);
	}
	i = -1;
	while (cache[++i])
		temp[i] = cache[i];
	j = -1;
	while (buffer[++j])
		temp[++i] = buffer[j];
	temp[j] = '\0';
	free(cache);
	cache = NULL;
	return (temp);
}
