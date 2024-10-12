/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:20 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/12 13:56:13 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_locals(t_data *data)
{
	t_env	*head;

	head = data->locals;
	while (data->locals)
	{
		printf("%s=%s\n", data->locals->variable, data->locals->value);
		data->locals = data->locals->next;
	}
	data->locals = head;
}

static void	check_l_variable(t_data *data, t_env *new_l_var, t_token *value)
{
	if (new_l_var)
	{
		free(new_l_var->value);
		if (value)
			new_l_var->value = ft_strdup(value->token);
		else
			new_l_var->value = ft_strdup("");
	}
	else
	{
		if (value)
		{
			new_l_var = new_variable(data->input.tokens->token, \
			value->token);
		}
		else
			new_l_var = new_variable(data->input.tokens->token, "");
		if (last_variable(data->locals))
			last_variable(data->locals)->next = new_l_var;
		else
			data->locals = new_l_var;
	}
}

void	add_locals(t_data *data)
{
	t_env	*new_l_var;
	t_token	*head;
	t_env	*env_var;

	head = data->input.tokens;
	while (data->input.tokens)
	{
		if (data->input.tokens->type == L_VARIABLE)
		{
			new_l_var = get_env_var(data->locals, data->input.tokens->token);
			check_l_variable(data, new_l_var, data->input.tokens->next);
			env_var = get_env_var(data->env, new_l_var->variable);
			if (env_var)
			{
				free(env_var->value);
				env_var->value = new_l_var->value;
			}
		}
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
}
