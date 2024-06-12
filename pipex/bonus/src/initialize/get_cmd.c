/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:44:22 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/12 17:18:50 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	here_doc_cmd(t_data *data)
{
	data->cmd = ft_calloc(3, sizeof(t_cmd));
	if (data->cmd == NULL)
		ft_error(data, "ft_calloc: " ALLOCF, NULL);
	data->cmd[0].opt = ft_split(data->argv[3], ' ');
	if (data->cmd[0].opt == NULL)
		ft_error(data, "ft_split: " ALLOCF, NULL);
	data->cmd[1].opt = ft_split(data->argv[4], ' ');
	if (data->cmd[1].opt == NULL)
		ft_error(data, "ft_split: " ALLOCF, NULL);
}

static void	not_here_doc_cmd(t_data *data)
{
	int	count;
	int	i;
	int	j;

	i = 1;
	j = -1;
	count = data->argc - 3;
	data->cmd = ft_calloc(count + 1, sizeof(t_cmd));
	if (data->cmd == NULL)
		ft_error(data, "ft_calloc: " ALLOCF, NULL);
	while (data->argv[++i] && ++j < count)
	{
		data->cmd[j].opt = ft_split(data->argv[i], ' ');
		if (data->cmd[j].opt == NULL)
			ft_error(data, "ft_split: " ALLOCF, NULL);
	}
}

void	get_cmd(t_data *data)
{
	if (data->here_doc_exists)
		here_doc_cmd(data);
	else
		not_here_doc_cmd(data);
}
