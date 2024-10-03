/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:39:54 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/03 15:26:23 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_built(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
		return (1);
	if (!ft_strncmp(cmd, "cd", len))
		return (1);
	if (!ft_strncmp(cmd, "pwd", len))
		return (1);
	if (!ft_strncmp(cmd, "export", len))
		return (1);
	if (!ft_strncmp(cmd, "unset", len))
		return (1);
	if (!ft_strncmp(cmd, "env", len))
		return (1);
	if (!ft_strncmp(cmd, "exit", len))
		return (1);
	return (0);
}

void	parse_cmd_opt(t_data *data)
{
	t_token	*tmp;

	tmp = data->input.tokens;
	while (tmp)
	{
		if (tmp->type == CMD && !is_built(tmp->token))
		{
		}
		tmp = tmp->next;
	}
}
