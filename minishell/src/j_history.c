/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/11 14:23:02 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

void	get_history(void)
{
	char	*ms_history;

	ms_history = "/tmp/.ms_history";
	if (ms_history)
		read_history(ms_history);
}

void	save_history(void)
{
	char	*ms_history;

	ms_history = "/tmp/.ms_history";
	if (ms_history)
		write_history(ms_history);
}
