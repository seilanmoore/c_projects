/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:51:43 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/02 10:51:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset_builtin(t_data *data)
{
	char			*variable;

	variable = data->input.tokens->next->token;
	if (get_env_var(data->env, variable))
		del_env(data->env, variable);
	upd_env(data);
	return (0);
}
