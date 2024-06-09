/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:59:16 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/09 11:32:28 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	initialize(t_data *data, int argc, char **argv, char **envp)
{
	*data = (t_data){0};
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->pipedes[0] = -1;
	data->pipedes[1] = -1;
	data->file[0].fd = -1;
	data->file[1].fd = -1;
}

void	init(t_data *data, int argc, char **argv, char **envp)
{
	initialize(data, argc, argv, envp);
	if (argc < 5)
		ft_error(data, "Must be at least 5 arguments", NULL);
}