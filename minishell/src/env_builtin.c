/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:50:43 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/17 12:18:22 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_builtin(t_data *data)
{
	int	i;

	if (!data->envp)
		return (0);
	i = -1;
	while (data->envp[++i])
		ft_putendl_fd(data->envp[i], 1);
	return (0);
}
