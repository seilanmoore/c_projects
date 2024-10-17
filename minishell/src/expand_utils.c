/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:15:47 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/17 12:18:22 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_home(t_data *data)
{
	char	*value;
	char	*tmp;

	if (data->input.tokens->token && \
		data->input.tokens->quote == NO_QUOTE && \
		(data->input.tokens->type == ARG || \
		data->input.tokens->type == FILE) && \
		*(data->input.tokens->token) == '~')
	{
		value = get_envp_var(data->envp, "HOME=");
		if (!value)
			value = get_envp_var(data->envp, "HOME=");
		tmp = str_replace(data->input.tokens->token, "~", value);
		free(data->input.tokens->token);
		data->input.tokens->token = tmp;
	}
}

char	*get_dollar_value(t_data *data, char *variable)
{
	t_env	*env_var;
	t_env	*local_head;

	if (!variable)
		return (NULL);
	if (!ft_strcmp(variable, "$"))
		return (data->process);
	if (!ft_strcmp(variable, "?"))
		return (data->prev_exit_code);
	env_var = get_env_var(data->env, variable);
	if (env_var)
		return (env_var->value);
	local_head = get_env_var(data->locals, variable);
	if (local_head)
		return (local_head->value);
	return (NULL);
}

char	*extract_id(char *token)
{
	char	*identifier;
	int		len;

	identifier = ft_strchr(token, '$');
	if ((identifier + 1) && identifier[1] == '$')
		return (ft_strdup("$$"));
	if ((identifier + 1) && identifier[1] == '?')
		return (ft_strdup("$?"));
	len = 1;
	while (identifier[len] && valid_char(identifier[len]))
		len++;
	return (ft_substr(identifier, 0, len));
}
