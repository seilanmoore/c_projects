/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:51:43 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/11 10:34:51 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset_builtin(t_data *data, t_token *token)
{
	char	*variable;

	(void)token;
	if (data->input.tokens->next && \
	(data->input.tokens->next->type == VARIABLE || \
	data->input.tokens->next->type == L_VARIABLE))
	{
		variable = data->input.tokens->next->token;
		if (get_env_var(data->env, variable))
			del_env(data->env, variable);
		upd_env(data);
	}
	return (0);
}
