/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:15:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/22 13:52:06 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	cmd_not_found(t_data *data)
{
	int	fail;
	int	i;

	i = -1;
	fail = 0;
	while (data->cmd[++i].opt)
	{
		if (data->cmd[i].path == NULL)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(data->cmd[i].opt[0], 2);
			ft_putstr_fd(PATHF "\n", 2);
			fail = 1;
		}
	}
	if (fail)
	{
		data->exit_code = 127;
		ft_error(data, NULL, NULL);
	}
}

static void	append_slash(t_data *data)
{
	char	*tmp;
	int		i;

	i = -1;
	while (data->paths[++i])
	{
		tmp = data->paths[i];
		data->paths[i] = ft_strjoin(data->paths[i], "/");
		free(tmp);
		if (data->paths[i] == NULL)
			ft_error(data, "ft_strjoin: " ALLOCF, NULL);
	}
}

static void	assign_paths(t_data *data)
{
	char	*cmd;
	int		i;
	int		j;

	i = -1;
	while (data->cmd[++i].opt)
	{
		j = -1;
		cmd = data->cmd[i].opt[0];
		while (data->paths[++j])
		{
			if (data->cmd[i].path == NULL)
			{
				data->cmd[i].path = ft_strjoin(data->paths[j], cmd);
				if (access(data->cmd[i].path, F_OK | X_OK) == ERROR)
				{
					free(data->cmd[i].path);
					data->cmd[i].path = NULL;
				}
			}
		}
	}
}

void	get_path(t_data *data)
{
	char	*line;
	int		i;

	line = NULL;
	i = -1;
	while (data->envp[++i])
	{
		if (!ft_strncmp("PATH=", data->envp[i], 5))
		{
			line = &(data->envp[i][5]);
			if (line[0] == '\0')
				ft_error(data, "PATH empty", NULL);
			data->paths = ft_split(line, ':');
			if (!data->paths)
				ft_error(data, "ft_split: " ALLOCF, NULL);
		}
	}
	if (data->paths == NULL)
		ft_error(data, "PATH variable not found", NULL);
	append_slash(data);
	assign_paths(data);
	cmd_not_found(data);
}
