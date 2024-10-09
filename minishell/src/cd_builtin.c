/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:48:46 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/09 16:50:23 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* static int	is_dir_check(char *path)
{
	struct stat	path_stat;
	char		*tmp;
	int			len;

	tmp = NULL;
	len = ft_strlen(path) - 1;
	if (path[len] == '/')
		tmp = ft_substr(path, 0, len);
	else
		tmp = ft_strdup(path);
	if (access(tmp, F_OK) == -1)
		return (free(tmp), 0);
	if (stat(tmp, &path_stat))
		return (free(tmp), 1);
	if (!S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": " NOT_DIR, 2);
		return (free(tmp), 1);
	}
	return (free(tmp), 0);
} */

static int	cd_path(t_data *data, t_token *token)
{
	if (chdir(token->arg->token) == -1)
	{
		if (errno == ENOTDIR)
		{
			ft_putstr_fd(MS, 2);
			ft_putstr_fd(token->arg->token, 2);
			ft_putendl_fd(": " NOT_DIR, 2);
			return (1);
		}
		if (errno == EACCES)
		{
			ft_putstr_fd(MS, 2);
			ft_putstr_fd(token->arg->token, 2);
			ft_putendl_fd(": " PERMIT, 2);
			return (1);
		}
		if (errno == ENOENT)
		{
			ft_putstr_fd(MS, 2);
			ft_putstr_fd(token->arg->token, 2);
			ft_putendl_fd(": " PATH_EXIST, 2);
			return (1);
		}
		if (access(token->arg->token, R_OK) == -1)
		{
			ft_putstr_fd(MS, 2);
			ft_putstr_fd(token->arg->token, 2);
			ft_putendl_fd(": " PERMIT, 2);
			return (1);
		}
		ft_putstr_fd(MS CD, 2);
		ft_putstr_fd(token->arg->token, 2);
		return (print_msg(data, ": " PATH_EXIST, -1), 1);
	}
	return (0);
}

static int	cd_home(t_data *data, t_token *token, t_env *home)
{
	if (!token->arg)
	{
		if (home && home->value)
		{
			if (chdir(home->value) == -1)
				return (1);
			return (0);
		}
		else
			return (print_msg(data, MS CD CD_HOME, -1), 1);
	}
	else if (cd_path(data, token) == 1)
		return (1);
	return (0);
}

int	cd_builtin(t_data *data, t_token *token)
{
	t_env	*home;
	t_env	*old_pwd;

	if (token->opt)
		return (print_msg(data, MS CD CD_OPT, -1), 1);
	if (token->arg && token->arg->next && token->arg->next->type == ARG)
		return (print_msg(data, MS CD CD_ARG, -1), 1);
	home = get_env_var(data->env, "HOME");
	if (cd_home(data, token, home) == 1)
		return (1);
	old_pwd = get_env_var(data->env, "OLDPWD");
	if (old_pwd)
	{
		free(old_pwd->value);
		old_pwd->value = ft_strdup(data->cwd);
		upd_env(data);
	}
	return (0);
}
