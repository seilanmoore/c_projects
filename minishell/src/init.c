/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:34 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/25 11:09:41 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	*data = (t_data){0};
	data->env = (t_environment *){0};
	data->local = (t_l_variable *){0};
	data->input = (t_input){0};
	data->envp = envp;
	data->argc = argc;
	data->argv = argv;
	data->status = -1;
}
