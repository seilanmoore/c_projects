/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:21:13 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/25 12:18:41 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	concatenate(t_data *data, t_token **new_lst)
{
	char	*full_str;
	char	*tmp;
	int		len;

	full_str = ft_strdup(data->input.tokens->token);
	len = ft_strlen(data->input.tokens->token);
	while (data->input.tokens->next && \
	!is_space(data->input.tokens->token[len - 1]))
	{
		tmp = full_str;
		full_str = ft_strjoin(full_str, data->input.tokens->token);
		data->input.tokens = data->input.tokens->next;
		len = ft_strlen(data->input.tokens->token);
		
	}
	add_back_token(new_lst, new_token(full_str, 0, data->input.tokens->prev->quote, int end_space))
}

void	concatenate_tokens(t_data *data)
{
	t_token	*new_lst;
	t_token	*head;
	int		len;

	head = data->input.tokens;
	while (data->input.tokens)
	{
		len = ft_strlen(data->input.tokens->token);
		if (is_space(data->input.tokens->token[len - 1]))
			concatenate(data, &(new_lst));
		else
		{
		
		}
	}
	data->input.tokens = head;
	set_prev_token(data);
	assign_types(data);
	free_tokens(data);
	data->input.tokens = new_lst;
}
