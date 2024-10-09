/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:15:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/07 11:02:13 by smoore-a         ###   ########.fr       */
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
	char	*line;
	int		i;

	line = NULL;
	i = -1;
	while (data->envp_cpy[++i] && ft_strncmp("PATH=", data->envp_cpy[i], 5))
		;
	if (!ft_strncmp("PATH=", data->envp_cpy[i], 5))
	{
		line = &(data->envp_cpy[i][5]);
		if (line[0] == '\0')
			printf(MS EMPTY_PATH NL);
		data->paths = ft_split(line, ':');
	}
	else
		printf(MS NO_PATH NL);
	append_slash(data);
}

void	assign_paths(t_data *data)
{
	t_cmd	*head;
	char	*cmd;
	int		i;

	if (!data->input.command)
		return ;
	get_env_paths(data);
	head = data->input.command;
	while (head)
	{
		if (!head->builtin && !ft_strchr(head->cmd, '/'))
		{
			i = -1;
			cmd = head->cmd;
			head->cmd = NULL;
			while (data->paths[++i] && head->cmd == NULL)
			{
				head->cmd = ft_strjoin(data->paths[i], cmd);
				if (access(head->cmd, F_OK | X_OK) == -1)
				{
					free(head->cmd);
					head->cmd = NULL;
				}
			}
			if (!head->cmd)
			{
				head->cmd = ft_strdup(cmd);
			}
		}
		else if (!head->builtin)
			head->cmd = ft_strdup(head->cmd);
		head = head->next;
	}
}
