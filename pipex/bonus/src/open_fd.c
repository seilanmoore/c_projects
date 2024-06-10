/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:31:32 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/10 09:26:23 by smoore-a         ###   ########.fr       */
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

void	open_fd(t_data *data)
{
	int	count;

	data->file[0].name = data->argv[1];
	if(ft_strncmp(data->argv[1], HERE_DOC, ft_strlen(data->argv[1])))
		data->file[0].fd = open(data->argv[1], O_RDONLY);
	else
		data->file[0].fd = open(_HERE_DOC, O_RDWR | O_CREAT);
	count = data->argc - 1;
	data->file[1].name = data->argv[count];
	data->file[1].fd = open(data->argv[count], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (data->file[0].fd == ERROR || data->file[1].fd == ERROR)
	{
		count = -1;
		while (++count < 2)
			file_error(data, data->file[count].name);
		ft_error(data, NULL, NULL);
	}
}