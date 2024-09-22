/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:13:57 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/22 14:16:46 by smoore-a         ###   ########.fr       */
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

//hacer copia en matriz de envp, pero no de la variable char **envp sino de t_environment *env

void	parse_environment(t_data *data)
{
	char			*variable;
	char			*value;
	int				len;
	int				i;

	i = -1;
	while (data->envp[++i])
	{
		len = ft_strchr(data->envp[i], '=') - data->envp[i];
		variable = ft_substr(data->envp[i], 0, len);
		value = ft_substr(data->envp[i], len + 1, ft_strlen(data->envp[i]));
		add_back_variable(&(data->env), new_variable(variable, value));
	}
	data->envp_cpy = ft_calloc(count_vars(data->envp) + 1, sizeof(char *));
	i = -1;
	while (data->envp[++i])
		data->envp_cpy[i] = ft_strdup(data->envp[i]);
	i = -1;
	while (data->envp_cpy[++i])
		printf("%s\n", data->envp_cpy[i]);
	//print_env(data);
}

