/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:15:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/01 14:43:05 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_new_var(t_data *data, t_environment *new_var)
{
	if (new_var)
	{
		free(new_var->value);
		if (data->input.tokens->next)
			new_var->value = ft_strdup(data->input.tokens->next->token);
		else
			new_var->value = ft_strdup("");
	}
	else
	{
		if (data->input.tokens->next)
		{
			new_var = new_variable(data->input.tokens->token,
					data->input.tokens->next->token);
		}
		else
			new_var = new_variable(data->input.tokens->token, "");
		last_variable(data->env)->next = new_var;
	}
}

int	export_builtin(t_data *data)
{
	t_environment	*new_var;
	t_tokens		*head;
	int				modified;
	int				valid_id;

	modified = 0;
	head = data->input.tokens;
	while (data->input.tokens)
	{
		valid_id = valid_char(data->input.tokens->token);
		if (data->input.tokens->type == VARIABLE && valid_id)
		{
			new_var = get_env_var(data->env, data->input.tokens->token);
			check_new_var(data, new_var);
			modified = 1;
		}
		else if (data->input.tokens->type == VARIABLE)
			print_msg(data, MS EXPORT EXPORT_ID, 1);
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
	if (modified)
		upd_env(data);
	return (0);
}

int	unset_builtin(t_data *data)
{
	char			*variable;

	variable = data->input.tokens->next->token;
	if (get_env_var(data->env, variable))
		del_env(data->env, variable);
	upd_env(data);
	return (0);
}

int	env_builtin(t_data *data)
{
	print_array(data->envp_cpy);
	return (0);
}

int	pwd_builtin(t_data *data)
{
	t_environment	*pwd;

	pwd = get_env_var(data->env, "PWD");
	if (pwd && pwd->value)
		return (ft_putendl_fd(pwd->value, 1), 0);
	return (-1);
}

int	cd_builtin(t_data *data, t_tokens *token)
{
	t_environment	*home;
	t_environment	*variable;
	char			*recover;

	if (token->opt)
		return (print_msg(data, MS CD CD_OPT, -1), 1);
	if (token->arg && token->arg->next && token->arg->next->type == ARG)
		return (print_msg(data, MS CD CD_ARG, -1), 1);
	home = get_env_var(data->env, "HOME");
	variable = get_env_var(data->env, "OLDPWD");
	recover = NULL;
	if (variable)
	{
		recover = ft_strdup(variable->value);
		free(variable->value);
		variable->value = ft_strdup(data->cwd);
		upd_env(data);
	}
	if (!data->input.tokens->next && home && home->value)
		chdir(home->value);
	else if (!data->input.tokens->next)
	{
		if (variable)
		{
			free(variable->value);
			variable->value = ft_strdup(recover);
		}
		free(recover);
		return (print_msg(data, MS CD CD_HOME, -1), 1);
	}
	else if (chdir(data->input.tokens->next->token) == -1)
	{
		if (variable)
		{
			free(variable->value);
			variable->value = ft_strdup(recover);
		}
		free(recover);
		ft_putstr_fd(MS CD, 2);
		ft_putstr_fd(data->input.tokens->next->token, 2);
		return (print_msg(data, ": " CD_EXIST, -1), 1);
	}
	return (free(recover), 0);
}

int	exit_builtin(t_data *data)
{
	ft_putendl_fd("exit", 1);
	free(data->prev_exit_code);
	free_local(data);
	free_environment(data);
	free_data(data);
	rl_clear_history();
	clear_history();
	exit(EXIT_SUCCESS);
}
