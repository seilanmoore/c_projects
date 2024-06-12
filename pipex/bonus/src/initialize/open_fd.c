/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:31:32 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/12 17:18:50 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	file_error(t_data *data, char *file)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(OPENF, 2);
	data->exit_code = errno;
}

static void	here_doc_open(t_data *data)
{
	data->fd[0] = open(_HERE_DOC, O_WRONLY | O_CREAT, 00644);
	data->fd[1] = open(data->argv[data->argc - 1], \
		O_WRONLY | O_CREAT | O_APPEND, 00644);
}

static void	not_here_doc_open(t_data *data)
{
	data->fd[0] = open(data->argv[1], O_RDONLY);
	data->fd[1] = open(data->argv[data->argc - 1], \
		O_WRONLY | O_CREAT | O_TRUNC, 00644);
}

void	open_fd(t_data *data)
{
	int	count;

	if (data->here_doc_exists)
		here_doc_open(data);
	else
		not_here_doc_open(data);
	count = data->argc - 1;
	if (data->fd[0] == ERROR)
		file_error(data, data->argv[1]);
	if (data->fd[1] == ERROR)
		file_error(data, data->argv[count]);
	if (data->exit_code == errno)
		ft_error(data, NULL, NULL);
}
