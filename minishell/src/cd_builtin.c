/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:48:46 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/12 17:47:11 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>
#include <unistd.h>

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

static int	cd_home(t_data *data, char *home)
{
	if (home)
	{
		if (chdir(home) == -1)
		{
			if (chdir(data->cwd) == -1)
			{
				if (chdir("/") == -1)
					return (1);
			}
			return (0);
		}
		return (0);
	}
	else
	{
		ft_putendl_fd(MS CD CD_HOME, 2);
		return (1);
	}
}

static int	handle_cwd_fail(t_data *data)
{
	char	*cwd;

	chdir(data->cwd);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		free(cwd);
		return (1);
	}
	chdir("/");
	return (0);
}

static int	cd_path(t_data *data, char *path, char *home)
{
	char	*cwd;

	if (!path)
		return (cd_home(data, home));
	if (chdir(path) == -1)
	{
		ft_putstr_fd(MS CD, 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (handle_cwd_fail(data) == 1)
			return (1);
	}
	free(cwd);
	return (0);
}

int	cd_builtin(t_data *data, t_cmd *cmd)
{
	t_env	*home;
	int		exit_;

	exit_ = 0;
	if (cmd->args[1] && cmd->args[1][0] == '-')
		return (print_msg(data, MS CD CD_OPT, -1), 1);
	if (cmd->args[1] && cmd->args[2])
		return (print_msg(data, MS CD CD_ARG, -1), 1);
	home = get_env_var(data->env, "HOME");
	if (home)
		exit_ = cd_path(data, cmd->args[1], home->value);
	else
		exit_ = cd_path(data, cmd->args[1], NULL);
	update_var(data);
	return (exit_);
}
