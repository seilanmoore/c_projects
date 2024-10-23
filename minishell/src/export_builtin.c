/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:49:42 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/23 22:36:21 by smoore-a         ###   ########.fr       */
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
	t_env	*new_var;
	char	*variable;
	int		len;
	int		modified;

	modified = 0;
	args = args->next;
	while (args && args->type == OPTION)
		args = args->next;
	while (args && args->type == ARG)
	{
		variable = args->token;
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
				printf("variable: /%s/\n", variable);
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
				printf("Llega\n");
				modified = 1;
				printf("variable: /%s/\n", variable);
			}
			free(variable);
		}
		args = args->next;
	}
	if (modified)
		upd_env(data);
	return (0);
}
