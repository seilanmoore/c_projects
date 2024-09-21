/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:05:26 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/21 10:16:28 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	its_var(char *input, int in_quote)
{
	char	*tmp;

	if (in_quote == 1)
		return (0);
	tmp = ft_strchr(input, '=');
	if(tmp && tmp + 1 && (*(tmp + 1) == '\'' || *(tmp + 1) == '\"'))
		return (1);
	return (0);
}

char	**handle_quotes(char *input)
{
	char	**tokens;
	int		i;

	i = -1;
	while (input[++i])
	{
		
	}
}
