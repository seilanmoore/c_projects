/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:15:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/05 06:30:04 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	cmd_not_found(t_data *data)
{
	if (data->cmd1p == NULL)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->cmd1[0], 2);
		ft_putstr_fd(PATHF "\n", 2);
	}
	if (data->cmd2p == NULL)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->cmd2[0], 2);
		ft_putstr_fd(PATHF "\n", 2);
	}
	data->exit_code = 127;
	ft_error(data, NULL, NULL);
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
	int	i;

	i = -1;
	while (data->paths[++i] && (data->cmd1p == NULL || data->cmd2p == NULL))
	{
		if (data->cmd1p == NULL)
		{
			data->cmd1p = ft_strjoin(data->paths[i], data->cmd1[0]);
			if (access(data->cmd1p, F_OK | X_OK) == ERROR)
			{
				free(data->cmd1p);
				data->cmd1p = NULL;
			}
		}
		if (data->cmd2p == NULL)
		{
			data->cmd2p = ft_strjoin(data->paths[i], data->cmd2[0]);
			if (access(data->cmd2p, F_OK | X_OK) == ERROR)
			{
				free(data->cmd2p);
				data->cmd2p = NULL;
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
	if (data->cmd1p == NULL || data->cmd2p == NULL)
		cmd_not_found(data);
}
