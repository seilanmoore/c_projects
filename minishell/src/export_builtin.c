/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:49:42 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/03 15:35:39 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_new_var(t_data *data, t_env *new_var)
{
	if (new_var)
	{
		free(new_var->value);
		if (data->input.tokens->next)
			new_var->value = ft_strdup(data->input.tokens->next->token);
		else
			new_var->value = ft_strdup("");
	}
	else
	{
		if (data->input.tokens->next)
		{
			new_var = new_variable(data->input.tokens->token,
					data->input.tokens->next->token);
		}
		else
			new_var = new_variable(data->input.tokens->token, "");
		last_variable(data->env)->next = new_var;
	}
}

int	export_builtin(t_data *data)
{
	t_env	*new_var;
	t_token	*head;
	int		modified;
	int		valid_id;

	modified = 0;
	head = data->input.tokens;
	while (data->input.tokens)
	{
		valid_id = valid_str(data->input.tokens->token);
		if (data->input.tokens->type == VARIABLE && valid_id)
		{
			new_var = get_env_var(data->env, data->input.tokens->token);
			check_new_var(data, new_var);
			modified = 1;
		}
		else if (data->input.tokens->type == VARIABLE)
			print_msg(data, MS EXPORT EXPORT_ID, 1);
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
	if (modified)
		upd_env(data);
	return (0);
}
