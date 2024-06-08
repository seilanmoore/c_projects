/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:59:16 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/08 13:46:36 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	initialize(t_data *data, int argc, char ***argv, char ***envp)
{
	data->argc = argc;
	data->argv = *argv;
}

void	init(t_data *data, int argc, char ***argv, char ***envp)
{
	initialize(data, argc, argv, envp);
}