/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:22:37 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/12 22:16:14 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	syntax_msg(char *wildcard)
{
	ft_putstr_fd(MS, 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(wildcard, 2);
	ft_putendl_fd("\'", 2);
}

int	is_redirection(int type)
{
	if (type == LEFT || type == LEFTT || type == RIGHT || type == RIGHTT)
		return (1);
	return (0);
}

int	is_word(int type)
{
	if (!type || type == PIPE || \
	type == LEFT || type == LEFTT || type == RIGHT || type == RIGHTT)
		return (0);
	return (1);
}

int	syntax_error(t_data *data)
{
	t_token	*token;

	token = data->input.tokens;
	if (circle_1(token))
		return (1);
	return (0);
}
