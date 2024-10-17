/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:13:57 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/17 13:52:15 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	envp_to_array(t_data *data)
{
	t_env	*head;
	char	*tmp;
	int		i;

	if (!data->env)
		return ;
	head = data->env;
	i = 0;
	data->envp = ft_calloc(env_size(data->env) + 1, sizeof(char *));
	while (data->env)
	{
		tmp = ft_strjoin(data->env->variable, "=");
		data->envp[i++] = ft_strjoin(tmp, data->env->value);
		free(tmp);
		data->env = data->env->next;
	}
	data->env = head;
}

void	envp_to_lst(t_data *data)
{
	char			*variable;
	char			*value;
	int				len;
	int				i;

	i = -1;
	if (!data->envp)
		return ;
	while (data->envp[++i])
	{
		len = ft_strchr(data->envp[i], '=') - data->envp[i];
		variable = ft_substr(data->envp[i], 0, len);
		value = ft_substr(
				data->envp[i], len + 1, ft_strlen(data->envp[i]));
		add_back_variable(&(data->env), new_variable(variable, value));
		free(variable);
		free(value);
	}
}

void	parse_environment(t_data *data)
{
	t_env	*variable;
	int		modified;

	envp_to_lst(data);
	printf("SHLVL from env_lst when parse environment: %s\n", get_env_var(data->env, "SHLVL")->value);
	modified = 0;
	//upd_env(data);
	/* variable = get_env_var(data->env, "OLDPWD");
	if (variable)
	{
		modified = 1;
		free(variable->value);
		variable->value = ft_strdup(data->cwd);
	}
	variable = get_env_var(data->env, "PWD");
	if (variable)
	{
		modified = 1;
		free(variable->value);
		variable->value = ft_strdup(data->cwd);
	}
	if (modified)
		upd_env(data); */
}
