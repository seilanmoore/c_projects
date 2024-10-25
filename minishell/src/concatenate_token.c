/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:21:13 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/25 14:02:00 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	concatenate(t_data *data, t_token **new_lst)
{
	char	*full_str;
	char	*tmp;


	full_str = ft_strdup(data->input.tokens->token);
	while (data->input.tokens->next && \
	!data->input.tokens->end_space)
	{
		tmp = full_str;
		full_str = ft_strjoin(full_str, data->input.tokens->next->token);
		data->input.tokens = data->input.tokens->next;
	}
	add_back_token(new_lst, new_token( \
	full_str, 0, data->input.tokens->quote, \
	data->input.tokens->end_space));
}

void	concatenate_tokens(t_data *data)
{
	t_token	*new_lst;
	t_token	*head;

	new_lst = (t_token *) {0};
	head = data->input.tokens;
	while (data->input.tokens)
	{
		concatenate(data, &(new_lst));
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
	free_tokens(data);
	data->input.tokens = new_lst;
	set_prev_token(data);
	assign_types(data);
}
