/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:51:43 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/28 13:45:20 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset_builtin(t_data *data, t_cmd *cmd)
{
	char	**arg;
	int		update;
	int		i;

	arg = cmd->args;
	update = 0;
	i = 0;
	while (arg[++i])
	{
		if (get_env_var(data->env, arg[i]))
		{
			del_env(&(data->env), arg[i]);
			update = 1;
		}
		if (get_env_var(data->locals, arg[i]))
			del_env(&(data->locals), arg[i]);
	}
	if (update)
		upd_env(data);
	return (0);
}
