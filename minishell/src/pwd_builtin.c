/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:52:14 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/05 10:32:00 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd_builtin(t_data *data)
{
	t_env	*pwd;

	pwd = get_env_var(data->env, "PWD");
	if (pwd && pwd->value)
		return (ft_putendl_fd(pwd->value, 1), 0);
	return (-1);
}
