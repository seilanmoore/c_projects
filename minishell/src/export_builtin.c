/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:49:42 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/12 12:56:10 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_new_var(t_data *data, t_env *new_var, char **var)
{
	if (new_var)
	{
		free(new_var->value);
		if (*(var + 1))
			new_var->value = ft_strdup(*(var + 1));
		else
			new_var->value = ft_strdup("");
	}
	else
	{
		if (*(var + 1))
			new_var = new_variable(*var, *(var + 1));
		else
			new_var = new_variable(*var, "");
		last_variable(data->env)->next = new_var;
	}
}

int	export_builtin(t_data *data, t_cmd *cmd)
{
	char	**arg;
	t_env	*new_var;
	int		modified;
	int		i;

	modified = 0;
	arg = cmd->args;
	i = 0;
	while (arg[i])
	{
		if (valid_ident(arg[i]))
		{
			new_var = get_env_var(data->env, arg[i]);
			check_new_var(data, new_var, &arg[i]);
			modified = 1;
		}
		else
			print_msg(data, MS EXPORT EXPORT_ID, 1);
		i += 2;
	}
	if (modified)
		upd_env(data);
	return (0);
}
