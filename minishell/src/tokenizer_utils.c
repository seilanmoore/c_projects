/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:03:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/26 10:57:55 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	end_space(t_var *var)
{
	char	*quotes;

	quotes = &(var->aux1[var->i]);
	while (*quotes && (*quotes == '\'' || *quotes == '\"'))
	{
		if (*quotes == '\'')
		{
			if (*(++quotes) == '\'')
				quotes++;
			else
				return (0);
		}
		else if (*quotes == '\"')
		{
			if (*(++quotes) == '\"')
				quotes++;
			else
				return (0);
		}
	}
	if (is_space(*quotes))
		return (1);
	return (0);
}

void	set_prev_token(t_data *data)
{
	t_token	*head;
	t_token	*prev;

	head = data->input.tokens;
	prev = head;
	if (!data->input.tokens)
		return ;
	data->input.tokens = data->input.tokens->next;
	while (data->input.tokens)
	{
		data->input.tokens->prev = prev;
		prev = data->input.tokens;
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
}

t_token	*last_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back_token(t_token **lst, t_token *node)
{
	if (lst && node)
	{
		if (*lst)
			last_token(*lst)->next = node;
		else
			*lst = node;
	}
}

t_token	*new_token(void *token, int type, int quote, int end_space)
{
	t_token	*new_node;

	if (!token)
		return (NULL);
	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->token = token;
	new_node->type = type;
	new_node->quote = quote;
	new_node->end_space = end_space;
	new_node->opt = NULL;
	new_node->arg = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}
