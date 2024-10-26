/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:48:46 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/26 18:11:27 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	update_var(t_data *data)
{
	t_env	*variable;

	variable = get_env_var(data->env, "OLDPWD");
	if (variable)
	{
		free(variable->value);
		variable->value = ft_strdup(data->cwd);
		upd_env(data);
	}
	variable = get_env_var(data->env, "PWD");
	if (variable)
	{
		free(variable->value);
		variable->value = getcwd(NULL, 0);
		upd_env(data);
	}
}

static int	cd_path(char *path, t_env *home)
{
	if (!path)
	{
		if (home)
		{
			if (home->value && *(home->value))
			{
				if (chdir(home->value) == -1 && handle_errno(home->value) == 1)
					return (1);
			}
			return (0);
		}
		return (ft_putendl_fd(MS CD CD_HOME, 2), 1);
	}
	else if (chdir(path) == -1 && handle_errno(path) == 1)
		return (1);
	return (0);
}

int	cd_builtin(t_data *data, t_cmd *cmd)
{
	t_env	*home;

	if (cmd->args[1][0] == '-')
		return (print_msg(data, MS CD CD_OPT, -1), 1);
	if (cmd->args[1] && cmd->args[2])
		return (print_msg(data, MS CD CD_ARG, -1), 1);
	home = get_env_var(data->env, "HOME");
	if (cd_path(cmd->args[1], home))
		return (1);
	update_var(data);
	return (0);
}
