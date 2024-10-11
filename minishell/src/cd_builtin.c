/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:48:46 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/11 10:35:30 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	cd_path(t_token *token, t_env *home)
{
	if (!token->arg)
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
	else if (chdir(token->arg->token) == -1 && \
	handle_errno(token->arg->token) == 1)
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
	if (cd_path(token, home) == 1)
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
