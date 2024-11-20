/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_circles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:44:49 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/12 16:48:50 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	circle_4(t_token *token, t_token *prev)
{
	if (token)
	{
		if (is_word(token->type))
			return (circle_3(token->next, token));
		if (is_redirection(token->type))
			return (circle_2(token->next, token));
	}
	return (syntax_msg(prev->token), 1);
}

int	circle_3(t_token *token, t_token *prev)
{
	if (!token)
		return (0);
	if (token->type == PIPE)
		return (circle_4(token->next, token));
	if (is_word(token->type))
		return (circle_3(token->next, token));
	if (is_redirection(token->type))
		return (circle_2(token->next, token));
	return (syntax_msg(prev->token), 1);
}

int	circle_2(t_token *token, t_token *prev)
{
	if (token)
	{
		if (is_word(token->type))
			return (circle_3(token->next, token));
	}
	return (syntax_msg(prev->token), 1);
}

int	circle_1(t_token *token)
{
	if (is_word(token->type))
		return (circle_3(token->next, token));
	if (is_redirection(token->type))
		return (circle_2(token->next, token));
	return (syntax_msg(token->token), 1);
}
