/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:49:42 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/12 09:40:39 by smoore-a         ###   ########.fr       */
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

static int	seek_and_replace(t_data *data, char *arg)
{
	t_env	*new_var;
	char	*variable;
	char	*equal;

	variable = NULL;
	equal = ft_strchr(arg, '=');
	if (equal)
		variable = ft_substr(arg, 0, equal - arg);
	if (id_error(data, arg, variable, 1))
	{
		free(variable);
		return (0);
	}
	if (variable)
	{
		new_var = get_env_var(data->env, variable);
		check_new_var(\
				&(data->env), new_var, variable, equal + 1);
		free(variable);
	}
	return (1);
}

int	export_builtin(t_data *data, t_cmd *cmd)
{
	char	**args;
	int		update;
	int		fail;
	int		i;

	fail = 0;
	update = 0;
	args = cmd->args;
	i = 0;
	while (args[++i])
	{
		if (seek_and_replace(data, args[i]))
			update = 1;
		else
			fail = 1;
	}
	if (update)
		upd_env(data);
	if (fail)
		return (1);
	return (0);
}
