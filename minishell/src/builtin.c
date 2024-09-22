/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:15:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/22 13:31:48 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_builtin(t_data *data)
{
	t_environment	*head;

	head = data->env;
	while (data->env)
	{
		printf("%s=%s\n", data->env->variable, data->env->value);
		data->env = data->env->next;
	}
	data->env = head;
}

void	exit_builtin(t_data *data)
{
	ft_putstr_fd("exit\n", 1);
	free_data(data);
	exit(EXIT_SUCCESS);
}
