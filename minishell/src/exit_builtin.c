/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:50:58 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/28 12:03:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_builtin(t_data *data)
{
	int	exit_;

	exit_ = -1;
	if (data && data->input.command && data->input.command->args[0])
		exit_ = ft_atoi(data->input.command->args[0]);
	ft_putendl_fd("exit", 1);
	ft_free(&(data->prev_exit_code));
	free_local(data);
	free_environment(data);
	free_data(data);
	rl_clear_history();
	clear_history();
	if (exit_ != -1)
		exit(exit_);
	exit(EXIT_SUCCESS);
}
