/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:20 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/25 11:21:57 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_locals(t_data *data)
{
	t_l_variable	*head;

	head = data->local;
	while (data->local)
	{
		printf("%s=%s\n", data->local->variable, data->local->value);
		data->local = data->local->next;
	}
	data->local = head;
}

static t_l_variable	*new_l_variable(void *variable, char *value)
{
	t_l_variable	*new_node;

	if (!variable)
		return (NULL);
	new_node = (t_l_variable *)malloc(sizeof(t_l_variable));
	if (!new_node)
		return (NULL);
	new_node->variable = ft_strdup(variable);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = ft_strdup("");
	new_node->next = NULL;
	return (new_node);
}

static t_l_variable	*last_l_variable(t_l_variable *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	check_l_variable(t_data *data, t_l_variable *new_l_var)
{
	if (new_l_var)
	{
		free(new_l_var->value);
		if (data->input.tokens->next)
			new_l_var->value = ft_strdup(data->input.tokens->next->token);
		else
			new_l_var->value = ft_strdup("");
	}
	else
	{
		if (data->input.tokens->next)
		{
			new_l_var = new_l_variable(data->input.tokens->token,
					data->input.tokens->next->token);
		}
		else
			new_l_var = new_l_variable(data->input.tokens->token, "");
		if (last_l_variable(data->local))
			last_l_variable(data->local)->next = new_l_var;
		else
			data->local = new_l_var;
	}
}

static t_l_variable	*get_l_var(t_l_variable *l_variables, char *l_variable)
{
	t_l_variable	*head;
	size_t			len;

	if (!l_variables || !l_variable)
		return (NULL);
	len = ft_strlen(l_variable);
	head = l_variables;
	while (l_variables)
	{
		if (ft_strlen(l_variables->variable) == len && \
			!ft_strncmp(l_variables->variable, l_variable, len))
			return (l_variables);
		l_variables = l_variables->next;
	}
	l_variables = head;
	return (NULL);
}

void	add_l_variables(t_data *data)
{
	t_l_variable	*new_l_var;
	t_tokens		*head;

	head = data->input.tokens;
	while (data->input.tokens)
	{
		if (data->input.tokens->type == L_VARIABLE)
		{
			new_l_var = get_l_var(data->local, data->input.tokens->token);
			check_l_variable(data, new_l_var);
		}
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
}
