/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:54:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/02 17:15:44 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	valid_char(char c)
{
	if (!c)
		return (0);
	if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && \
	(c < '0' || c > '9') && c != '_')
		return (0);
	return (1);
}

int	no_word(int c)
{
	if (c == '<' || \
	c == '>' || \
	c == '|')
		return (1);
	return (0);
}

int	is_redir(int c)
{
	if (c == LEFT || \
	c == LEFTT || \
	c == RIGHT || \
	c == RIGHTT)
		return (1);
	return (0);
}

int	is_space(int c)
{
	if (c && (\
	c == ' ' || \
	c == '\t' || \
	c == '\n' || \
	c == '\r' || \
	c == '\f' || \
	c == '\v'))
		return (1);
	return (0);
}

int	is_cmd(int c)
{
	if (c && (\
	(c >= 'a' && c <= 'z') || \
	(c >= 'A' && c <= 'Z') || \
	(c >= '0' && c <= '9') || \
	c == '$' || \
	c == '*' || \
	c == '/' || \
	c == '.' || \
	c == '-' || \
	c == '_' || \
	c == '\\'))
		return (1);
	return (0);
}
