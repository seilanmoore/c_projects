/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:15:54 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/12 12:25:50 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	assign_opt_arg(t_data *data)
{
	t_token	*tmp;
	t_token	*aux;

	tmp = data->input.tokens;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			aux = tmp->next;
			while (aux && \
			(aux->type == OPTION || aux->type == ARG))
			{
				if (aux->type == OPTION && !tmp->opt)
					tmp->opt = aux;
				else if (aux->type == ARG && !tmp->arg)
					tmp->arg = aux;
				aux = aux->next;
			}
		}
		tmp = tmp->next;
	}
}

void	remove_equal(t_data *data)
{
	t_token	*head;
	char	*tmp;

	if (!data->input.tokens)
		return ;
	head = data->input.tokens;
	while (data->input.tokens)
	{
		if (data->input.tokens->type == L_VARIABLE)
		{
			tmp = data->input.tokens->token;
			data->input.tokens->token = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
			free(tmp);
		}
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
}

void	access_to_types(t_data *data, int target, int type)
{
	t_token	*head;
	int		i;

	head = data->input.tokens;
	i = -1;
	while (++i != target)
		data->input.tokens = data->input.tokens->next;
	if (data->input.tokens)
		data->input.tokens->type = type;
	data->input.tokens = head;
}

void	assign_types(t_data	*data)
{
	t_token	*ptr;
	int		i;

	ptr = data->input.tokens;
	i = 0;
	while (ptr)
	{
		type_checks(data, ptr, i);
		ptr = ptr->next;
		i++;
	}
}
