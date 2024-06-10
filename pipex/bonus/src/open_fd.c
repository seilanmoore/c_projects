/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:31:32 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/10 20:23:55 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	file_error(t_data *data, char *file)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(OPENF, 2);
	data->exit_code = errno;
}

static void	here_doc_file(t_data *data)
{
	data->file[0].fd = open(_HERE_DOC, O_WRONLY | O_CREAT, 00644);
	data->file[1].fd = open(data->argv[data->argc - 1], \
		O_WRONLY | O_CREAT | O_APPEND, 00644);
	data->file[0].opened = 1;
	data->file[1].opened = 1;
}

static void	not_here_doc_file(t_data *data)
{
	data->file[0].fd = open(data->argv[1], O_RDONLY);
	data->file[1].fd = open(data->argv[data->argc - 1], \
		O_WRONLY | O_CREAT | O_TRUNC, 00644);
	data->file[0].opened = 1;
	data->file[1].opened = 1;
}

void	open_fd(t_data *data)
{
	int	count;

	if (data->here_doc_exits)
		here_doc_file(data);
	else
		not_here_doc_file(data);
	count = data->argc - 1;
	data->file[0].name = data->argv[1];
	data->file[1].name = data->argv[count];
	count = -1;
	while (++count < 2)
	{
		if (data->file[count].fd == ERROR)
			file_error(data, data->file[count].name);
	}
	count = -1;
	while (++count < 2)
	{
		if (data->file[count].fd == ERROR)
			ft_error(data, NULL, NULL);
	}
}
