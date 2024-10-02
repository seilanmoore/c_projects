/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:13:57 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/02 12:41:48 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_env(t_data *data)
{
	void	*head;

	head = data->env;
	while (data->env)
	{
		printf("VARIABLE: \'%s\'\nVALUE: \'%s\'\n", data->env->variable, data->env->value);
		data->env = data->env->next;
	}
	data->env = head;
}

int	count_vars(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		;
	return (i);
}

void	copy_envp(t_data *data)
{
	int	i;

	if (!data->envp)
		return ;
	data->envp_cpy = ft_calloc(count_vars(data->envp) + 1, sizeof(char *));
	if (!data->envp_cpy)
		return ;
	i = -1;
	while (data->envp[++i])
		data->envp_cpy[i] = ft_strdup(data->envp[i]);
}

void	envp_to_array(t_data *data)
{
	t_environment	*head;
	char			*tmp;
	int				i;

	if (!data->env)
		return ;
	head = data->env;
	i = 0;
	data->envp_cpy = ft_calloc(env_size(data->env) + 1, sizeof(char *));
	while (data->env)
	{
		tmp = ft_strjoin(data->env->variable, "=");
		data->envp_cpy[i++] = ft_strjoin(tmp, data->env->value);
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
	if (!data->envp_cpy)
		return ;
	while (data->envp_cpy[++i])
	{
		len = ft_strchr(data->envp_cpy[i], '=') - data->envp_cpy[i];
		variable = ft_substr(data->envp_cpy[i], 0, len);
		value = ft_substr(
				data->envp_cpy[i], len + 1, ft_strlen(data->envp_cpy[i]));
		add_back_variable(&(data->env), new_variable(variable, value));
		free(variable);
		free(value);
	}
}

void	parse_environment(t_data *data)
{
	t_environment	*variable;

	if (!data->envp_cpy)
	{
		copy_envp(data);
		envp_to_lst(data);
		variable = get_env_var(data->env, "OLDPWD");
		if (variable)
		{
			free(variable->value);
			variable->value = ft_strdup(data->cwd);
			upd_env(data);
		}
	}
	variable = get_env_var(data->env, "PWD");
	if (variable)
	{
		free(variable->value);
		variable->value = ft_strdup(data->cwd);
		upd_env(data);
	}
}
