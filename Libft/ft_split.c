/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:16:43 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/11 13:29:47 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*create_word(char const *s, size_t *i, char c)
{
	size_t	k;
	char	*word;

	k = 0;
	word = (char *)malloc(sizeof(char) * (strlen(s) + 1));
	if (!word)
		return (NULL);
	while (s[*i] && s[*i] != c)
		word[k++] = s[(*i)++];
	word[k] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	split = (char **)malloc(sizeof(char *) * (strlen(s) + 1));
	if (!s || !(split))
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			split[j] = create_word(s, &i, c);
			if (!(split[j]))
				return (NULL);
			j++;
		}
		else
			i++;
	}
	split[j] = NULL;
	return (split);
}
