/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:45:47 by smoore-a          #+#    #+#             */
/*   Updated: 2023/10/05 18:25:33 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>

#include <string.h> */

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	i;

	dest_len = 0;
	src_len = 0;
	i = 0;
	while (dest[dest_len] && dest_len < size)
		dest_len++;
	while (src[src_len])
		src_len++;
	while (src[i] && dest_len + i + 1 < size)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (dest_len < size)
		dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

/* int	main(void)
{
	char	dest[10] = "Hello, ";
	char	*src = "world!";
	unsigned int full_len = ft_strlcat(dest, src, sizeof(dest));
	//unsigned int full_len = strlcat(dest, src, sizeof(dest));

	printf("Concatenated string: %s\n", dest);
	printf("Total size if not truncated: %d\n", full_len);
	return (0);
} */
