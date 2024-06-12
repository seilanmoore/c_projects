/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:59:16 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/12 17:18:50 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	initialize(t_data *data, int argc, char **argv, char **envp)
{
	*data = (t_data){0};
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->cmdc = argc - 3;
	data->exit_code = -1;
}

static void	check_argc(t_data *data)
{
	if (data->argc < 5)
		ft_error(data, USAGE ARGS_P "\npipex: " USAGE HERE_DOC_P, NULL);
	else if (data->argv)
	{
		if (!ft_strncmp(HERE_DOC, data->argv[1], ft_strlen(data->argv[1])))
			data->here_doc_exists = 1;
		if (data->here_doc_exists && data->argc != 6)
			ft_error(data, USAGE HERE_DOC_P, NULL);
		else if (!data->here_doc_exists && data->argc < 5)
			ft_error(data, USAGE ARGS_P, NULL);
	}
	if (data->envp == NULL)
		ft_error(data, "environment variables not found", NULL);
}

void	init(t_data *data, int argc, char **argv, char **envp)
{
	initialize(data, argc, argv, envp);
	check_argc(data);
	check_permission(data);
	open_fd(data);
	get_cmd(data);
	get_path(data);
}
