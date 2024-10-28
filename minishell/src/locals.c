/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:20 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/28 11:49:59 by smoore-a         ###   ########.fr       */
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

static void	mod_env_value(t_env *node, char *new_value)
{
	if (node)
	{
		free(node->value);
		if (new_value)
			node->value = ft_strdup(new_value);
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

static void	add_local(t_data *data, char *token)
{
	t_env	*node;
	char	*variable;
	char	*equal;

	variable = NULL;
	equal = ft_strchr(token, '=');
	if (equal)
		variable = ft_substr(token, 0, equal - token);
	if (!valid_ident(variable))
	{
		ft_putstr_fd(MS "`", 1);
		ft_putstr_fd(token, 1);
		print_msg(data, "': " EXPORT_ID, 1);
	}
	else
	{
		node = get_env_var(data->env, variable);
		mod_env_value(node, equal + 1);
		node = get_loc_var(data->locals, variable);
		mod_loc_value(&(data->locals), node, variable, equal + 1);
	}
	free(variable);
}

void	locals(t_data *data)
{
	t_token	*tmp;

	tmp = data->input.tokens;
	while (tmp)
	{
		if (tmp->type == LOCAL)
			add_local(data, tmp->token);
		tmp = tmp->next;
	}
}
