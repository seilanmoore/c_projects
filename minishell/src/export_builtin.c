/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:49:42 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/28 10:22:48 by smoore-a         ###   ########.fr       */
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

int	export_builtin(t_data *data, t_cmd *cmd)
{
	t_env	*new_var;
	char	**args;
	char	*variable;
	char	*equal;
	int		modified;
	int		i;

	modified = 0;
	args = cmd->args;
	i = 0;
	while (args[++i])
	{
		variable = NULL;
		equal = ft_strchr(args[i], '=');
		if (equal)
			variable = ft_substr(args[i], 0, equal - args[i]);
		if (!valid_ident(variable))
		{
			ft_putstr_fd(MS EXPORT "`", 1);
			ft_putstr_fd(args[i], 1);
			print_msg(data, "': " EXPORT_ID, 1);
		}
		else
		{
			new_var = get_env_var(data->env, variable);
			check_new_var(\
					&(data->env), new_var, variable, equal + 1);
			modified = 1;
		}
		free(variable);
	}
	if (modified)
		upd_env(data);
	return (data->status);
}
