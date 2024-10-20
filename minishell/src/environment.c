/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:13:57 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/19 10:06:35 by smoore-a         ###   ########.fr       */
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

	free_env_lst(data);
	if (!data->envp)
		return ;
	i = -1;
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
