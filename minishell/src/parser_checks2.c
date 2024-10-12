/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:14:41 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/12 20:51:16 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_option_arg(t_data *data, t_token *ptr, int i)
{
	if (ptr->prev)
	{
		if (ptr->quote == NO_QUOTE && \
			ptr->token[0] == '-' && \
			(ptr->prev->type == CMD || ptr->prev->type == OPTION))
			return (access_to_types(data, i, OPTION), 1);
		if (ptr->prev->type == CMD || \
			ptr->prev->type == OPTION || \
			ptr->prev->type == ARG)
			return (access_to_types(data, i, ARG), 1);
	}
	return (0);
}

int	check_cmds(t_data *data, t_token *ptr, int i)
{
	int	x;

	if (check_option_arg(data, ptr, i))
		return (1);
	x = -1;
	while (ptr->token[++x])
	{
		if (!is_cmd(ptr->token[x]))
			return (0);
	}
	data->n_cmd++;
	access_to_types(data, i, CMD);
	return (1);
}
