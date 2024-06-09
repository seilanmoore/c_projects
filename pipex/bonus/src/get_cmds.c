/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:44:22 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/09 22:30:04 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	get_cmds(t_data *data)
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
