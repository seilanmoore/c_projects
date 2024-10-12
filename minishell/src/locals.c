/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:20 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/12 21:02:39 by smoore-a         ###   ########.fr       */
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

static void	check_l_variable(t_data *data, t_env *new_l_var, char *value)
{
	if (new_l_var)
	{
		free(new_l_var->value);
		if (value)
			new_l_var->value = ft_strdup(value);
		else
			new_l_var->value = ft_strdup("");
	}
	else
	{
		if (value)
			new_l_var = new_variable(data->input.tokens->token, value);
		else
			new_l_var = new_variable(data->input.tokens->token, "");
		if (last_variable(data->locals))
			last_variable(data->locals)->next = new_l_var;
		else
			data->locals = new_l_var;
	}
}

static char	**split_local(char *local)
{
	char	**array;
	int		i;

	array = ft_calloc(3, sizeof(char *));
	i = -1;
	while (local[++i])
	{
		if (local[i] == '=')
		{
			array[0] = ft_substr(local, 0, i);
			array[1] = ft_strdup(&local[++i]);
			return (array);
		}
	}
	return (NULL);
}

static void	add_local(t_data *data)
{
	t_env	*new_l_var;
	t_env	*env_var;
	char	**local;

	local = split_local(data->input.tokens->token);
	if (!local)
		return ;
	new_l_var = get_env_var(data->locals, local[0]);
	check_l_variable(data, new_l_var, local[1]);
	env_var = get_env_var(data->env, new_l_var->variable);
	if (env_var)
	{
		free(env_var->value);
		env_var->value = new_l_var->value;
	}
	free_array(local);
}

void	locals(t_data *data)
{
	t_token	*head;

	head = data->input.tokens;
	while (data->input.tokens)
	{
		if (data->input.tokens->type == LOCAL)
			add_local(data);
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
}
