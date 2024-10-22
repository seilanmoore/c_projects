/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:49:42 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/22 16:32:16 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_new_var(t_env **lst, t_env *new_var, char **var)
{
	if (new_var)
	{
		free(new_var->value);
		if (var[1])
			new_var->value = ft_strdup(var[1]);
		else
			new_var->value = ft_strdup("");
	}
	else
	{
		if (var[1])
			new_var = new_variable(var[0], var[1]);
		else
			new_var = new_variable(var[0], "");
		if (last_variable(*lst))
			last_variable(*lst)->next = new_var;
		else
			*lst = new_var;
	}
}

// Me llegan los argumentos separados y los necesito juntos (var="value")

int	export_builtin(t_data *data, t_cmd *cmd)
{
	char	**arg;
	t_env	*new_var;
	int		modified;
	int		i;
	char	**token;

	print_cmd_array(data);
	exit(0);
	modified = 0;
	arg = cmd->args;
	i = -1;
	while (arg[++i])
	{
		token = split_token(arg[i]);
		if (!token)
			return (0);
		if (valid_ident(token[0]))
		{
			new_var = get_env_var(data->env, token[0]);
			check_new_var(&(data->env), new_var, token);
			modified = 1;
		}
		else
			print_msg(data, MS EXPORT EXPORT_ID, 1);
	}
	if (modified)
		upd_env(data);
	return (0);
}
