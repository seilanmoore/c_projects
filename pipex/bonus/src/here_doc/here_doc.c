/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:11:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/10 08:32:02 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	assign_cmd(t_data *data)
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

void	here_doc(t_data *data)
{
	assign_cmd(data);
}
