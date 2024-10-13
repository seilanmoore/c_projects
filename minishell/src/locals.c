/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:20 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/13 20:03:35 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_locals(t_data *data)
{
	t_env	*head;

	head = data->locals;
	while (data->locals)
	{
		printf("%s=%s\n", data->locals->variable, data->locals->value);
		data->locals = data->locals->next;
	}
	data->locals = head;
}

/* static void	check_l_variable(t_data *data, t_env *new_l_var, char **local)
{
	if (new_l_var)
	{
		free(new_l_var->value);
		if (local[1])
			new_l_var->value = ft_strdup(local[1]);
		else
			new_l_var->value = ft_strdup("");
	}
	else
	{
		if (local[1])
			new_l_var = new_variable(local[0], local[1]);
		else
			new_l_var = new_variable(local[0], "");
		if (last_variable(data->locals))
			last_variable(data->locals)->next = new_l_var;
		else
			data->locals = new_l_var;
	}
} */

//está rota, new_local no se asigna bien

static void	add_local(t_data *data)
{
	t_env	*new_local;
	t_env	*env_var;
	char	**local;

	local = split_token(data->input.tokens->token);
	if (!local)
		return ;
	if (!valid_ident(local[0]))
	{
		ft_putstr_fd(MS "`", 2);
		ft_putstr_fd(local[0], 2);
		ft_putendl_fd("\': " EXPORT_ID, 2);
		free_array(local);
		return ;
	}
	new_local = get_env_var(data->locals, local[0]);
	check_new_var(&(data->locals), new_local, local);
	env_var = get_env_var(data->env, local[0]);
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ft_strdup(local[1]);
	}
	free_array(local);
}

void	locals(t_data *data)
{
	t_token	*head;

	head = data->input.tokens;
	while (data->input.tokens)
	{
		if (data->input.tokens->type == LOCAL)
			add_local(data);
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
}
