/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:01:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/12 17:58:15 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	free_strings(char ***str)
{
	int	i;

	if (*str)
	{
		i = -1;
		while ((*str)[++i])
		{
			free((*str)[i]);
			(*str)[i] = NULL;
		}
		free(*str);
		*str = NULL;
	}
}

void	cleanup(t_data *data)
{
	int	i;

	if (data)
	{
		unlink(_HERE_DOC);
		free_strings(&(data->paths));
		if (data->cmd)
		{
			i = -1;
			while (data->cmd[++i].opt)
			{
				free_strings(&(data->cmd[i].opt));
				if (data->cmd[i].path)
					free(data->cmd[i].path);
			}
			free(data->cmd);
		}
		*data = (t_data){0};
	}
}
