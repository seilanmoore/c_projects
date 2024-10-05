/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:13:34 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/05 10:58:22 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_redirections(t_data *data, t_token *ptr, int i)
{
	if (ptr->quote != NO_QUOTE)
		return (0);
	if (ft_strlen(ptr->token) == 1)
	{
		if (ptr->token[0] == '|')
			return (data->n_pipe++, access_to_types(data, i, PIPE), 1);
		else if (ptr->token[0] == '<')
			return (access_to_types(data, i, LEFT), 1);
		else if (ptr->token[0] == '>')
			return (access_to_types(data, i, RIGHT), 1);
	}
	else if (ft_strlen(ptr->token) == 2)
	{
		if (!ft_strncmp(ptr->token, ">>", 2))
			return (access_to_types(data, i, RIGHTT), 1);
		else if (!ft_strncmp(ptr->token, "<<", 2))
			return (access_to_types(data, i, LEFTT), 1);
	}
	return (0);
}

static int	check_files(t_data *data, t_token *ptr, int i)
{
	if (ptr->prev && \
		(ptr->prev->type == LEFT || \
		ptr->prev->type == RIGHT || \
		ptr->prev->type == RIGHTT))
		return (access_to_types(data, i, FILE), 1);
	return (0);
}

static int	check_local_variables(t_data *data, t_token *ptr, int i)
{
	if (!ptr->prev && ptr->quote == NO_QUOTE && \
		ptr->token[ft_strlen(ptr->token) - 1] == '=')
		return (access_to_types(data, i, L_VARIABLE), 1);
	if (ptr->prev && ptr->prev->type == L_VARIABLE)
		return (access_to_types(data, i, L_VALUE), 1);
	return (0);
}

static int	check_variables(t_data *data, t_token *ptr, int i)
{
	if (ptr->quote == NO_QUOTE && \
		ptr->token[ft_strlen(ptr->token) - 1] == '=')
		return (access_to_types(data, i, VARIABLE), 1);
	if (ptr->prev && ptr->prev->type == VARIABLE)
		return (access_to_types(data, i, VALUE), 1);
	return (0);
}

int	type_checks(t_data *data, t_token *ptr, int i)
{
	if (check_redirections(data, ptr, i))
		return (1);
	if (check_files(data, ptr, i))
		return (1);
	if (check_local_variables(data, ptr, i))
		return (1);
	if (check_variables(data, ptr, i))
		return (1);
	if (check_heredoc(data, ptr, i))
		return (1);
	return (check_cmds(data, ptr, i));
}
