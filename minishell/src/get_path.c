/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:15:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/14 13:58:51 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

static void	append_slash(t_data *data)
{
	char	*tmp;
	int		i;

	i = -1;
	while (data->paths[++i])
	{
		if (data->paths[i][ft_strlen(data->paths[i]) - 1] != '/')
		{
			tmp = data->paths[i];
			data->paths[i] = ft_strjoin(tmp, "/");
			free(tmp);
		}
	}
}

static void	get_env_paths(t_data *data)
{
	t_env	*tmp;
	char	*line;

	line = NULL;
	tmp = data->env;
	while (tmp && ft_strcmp("PATH", tmp->variable))
		tmp = tmp->next;
	if (tmp)
	{
		line = tmp->value;
		if (line[0])
			data->paths = ft_split(line, ':');
		append_slash(data);
	}
}

void	assign_paths(t_data *data)
{
	t_cmd	*head;
	char	*path;
	int		i;

	get_env_paths(data);
	head = data->input.command;
	while (head)
	{
		if (!head->builtin && !ft_strchr(head->cmd, '/'))
		{
			i = 0;
			path = ft_strjoin(data->paths[i], head->cmd);
			while (access(path, F_OK | X_OK) == -1)
			{
				free(path);
				path = ft_strjoin(data->paths[++i], head->cmd);
			}
			if (access(path, F_OK | X_OK) != -1)
			{
				free(head->cmd);
				head->cmd = path;
			}
		}
		head = head->next;
	}
}
