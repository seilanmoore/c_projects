/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:20 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/12 16:54:33 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	mod_env_value(t_env *node, char *value)
{
	if (node)
	{
		free(node->value);
		if (value)
			node->value = ft_strdup(value);
		else
			node->value = ft_strdup("");
	}
}

static t_env	*get_loc_var(t_env *locals, char *variable)
{
	while (locals)
	{
		if (!ft_strcmp(locals->variable, variable))
			return (locals);
		locals = locals->next;
	}
	return (locals);
}

static void	mod_loc_value(t_env **lst, t_env *node, char *var, char *val)
{
	if (node)
	{
		free(node->value);
		if (val)
			node->value = ft_strdup(val);
		else
			node->value = ft_strdup("");
	}
	else
	{
		if (val)
			add_back_variable(lst, new_variable(var, val));
		else
			add_back_variable(lst, new_variable(var, ""));
	}
}

static int	add_local(t_data *data, char *token)
{
	t_env	*node;
	char	*variable;
	char	*equal;

	variable = NULL;
	equal = ft_strchr(token, '=');
	if (equal)
		variable = ft_substr(token, 0, equal - token);
	if (id_error(data, token, variable, 0))
	{
		free(variable);
		return (0);
	}
	if (variable)
	{
		node = get_env_var(data->env, variable);
		mod_env_value(node, equal + 1);
		node = get_loc_var(data->locals, variable);
		mod_loc_value(&(data->locals), node, variable, equal + 1);
		free(variable);
	}
	return (1);
}

int	locals(t_data *data)
{
	t_token	*tmp;
	int		update;
	int		fail;

	fail = 0;
	update = 0;
	tmp = data->input.tokens;
	while (tmp)
	{
		if (tmp->type == LOCAL)
		{
			if (add_local(data, tmp->token) == 1)
				update = 1;
			else
				fail = 1;
		}
		tmp = tmp->next;
	}
	if (update)
		upd_env(data);
	if (fail)
		return (127);
	return (0);
}
