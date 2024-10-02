/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:50:58 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/02 12:42:00 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_builtin(t_data *data)
{
	ft_putendl_fd("exit", 1);
	free(data->prev_exit_code);
	free_local(data);
	free_environment(data);
	free_data(data);
	rl_clear_history();
	clear_history();
	exit(EXIT_SUCCESS);
}
