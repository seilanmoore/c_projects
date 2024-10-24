/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:49:42 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/24 20:45:13 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_new_var(t_env **lst, t_env *new_var, char *var, char *value)
{
	if (new_var)
	{
		free(new_var->value);
		if (value)
			new_var->value = ft_strdup(value);
		else
			new_var->value = ft_strdup("");
	}
	else
	{
		if (value)
			new_var = new_variable(var, value);
		else
			new_var = new_variable(var, "");
		if (last_variable(*lst))
			last_variable(*lst)->next = new_var;
		else
			*lst = new_var;
	}
}

int	export_builtin(t_data *data, t_token *args)
{
	t_token	*head;
	t_env	*new_var;
	char	*variable;
	char	*value;
	//int		len;
	int		modified;


	head = data->input.tokens;
	while (data->input.tokens && data->input.tokens->type != CMD \
	&& ft_strcmp(data->input.tokens->token, "export"))
		data->input.tokens = data->input.tokens->next;
	modified = 0;
	args = data->input.tokens;
	while (args && args->type == OPTION)
		args = args->next;
	while (args && args->type == ARG)
	{
		variable = variable_append(&(args));
		if (variable)
		{
			if (!valid_ident(variable))
				print_msg(data, MS EXPORT EXPORT_ID, 1);
			else
			{
				value = variable_append(&(args));
				new_var = get_env_var(data->env, variable);
				check_new_var(\
						&(data->env), new_var, variable, value);
				modified = 1;
				free(value);
			}
			free(variable);
		}
		/* variable = args->token;
		len = ft_strlen(variable);
		if (ft_strchr(variable, '=') && variable[len - 1] == '=')
		{
			variable = ft_substr(variable, 0, len - 1);
			if (!valid_ident(variable))
				print_msg(data, MS EXPORT EXPORT_ID, 1);
			else
			{
				new_var = get_env_var(data->env, variable);
				if (args->next && args->next->type == ARG && \
				args->end_space == 0 && ft_strchr(args->next->token, '='))
					check_new_var(\
						&(data->env), new_var, variable, args->next->token);
				else
					check_new_var(\
						&(data->env), new_var, variable, NULL);
				modified = 1;
			}
			free(variable);
		}
		else if (ft_strchr(variable, '='))
		{
			variable = ft_substr(\
				variable, 0, ft_strchr(variable, '=') - variable);
			if (!valid_ident(variable))
				print_msg(data, MS EXPORT EXPORT_ID, 1);
			else
			{
				new_var = get_env_var(data->env, variable);
				check_new_var(&(data->env), new_var, \
					variable, ft_strchr(args->token, '=') + 1);
				modified = 1;
			}
			free(variable);
		}
		else if (args->end_space == 0 && args->next && *(args->next->token) == '=')
		{
			variable = args->token;
			if (!valid_ident(variable))
				print_msg(data, MS EXPORT EXPORT_ID, 1);
			else
			{
				new_var = get_env_var(data->env, variable);
				if (*(args->next->token + 1))
					check_new_var(&(data->env), new_var, \
						variable, args->next->token + 1);
				else if (args->next->end_space == 0 && args->next->next)
				{
					check_new_var(&(data->env), new_var, \
						variable, args->next->next->token);
				}
				modified = 1;
			}
			free(variable);
		}
		args = args->next; */
	}
	if (modified)
		upd_env(data);
	data->input.tokens = head;
	return (0);
}
