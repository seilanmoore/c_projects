/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/01 12:50:10 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_dollar_value(t_data *data, char *variable)
{
	t_environment	*env_var;
	t_l_variable	*local_head;

	if (!variable)
		return (NULL);
	if (!ft_strncmp(variable, "$", ft_strlen(variable)))
		return (data->process);
	if (!ft_strncmp(variable, "?", ft_strlen(variable)))
		return (data->prev_exit_code);
	env_var = get_env_var(data->env, variable);
	if (env_var)
		return (env_var->value);
	local_head = get_l_var(data->local, variable);
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
	len = 1;
	while (identifier[len] && identifier[len] != '$' && \
		identifier[len] != '=' && identifier[len] != ' ' && \
		!g_signal)
		len++;
	return (ft_substr(identifier, 0, len));
}

void	expand(t_data *data)
{
	t_tokens	*token_head;
	char		*tmp;
	char		*identifier;
	char		*value;

	token_head = data->input.tokens;
	while (data->input.tokens && !g_signal)
	{
		while (ft_strchr(data->input.tokens->token, '$') && \
			*(ft_strchr(data->input.tokens->token, '$') + 1) && !g_signal)
		{
			tmp = data->input.tokens->token;
			identifier = extract_id(tmp);
			value = get_dollar_value(data, identifier + 1);
			data->input.tokens->token = str_replace(tmp, identifier, value);
			free(tmp);
			free(identifier);
		}
		if (data->input.tokens->token && \
			data->input.tokens->quote == NO_QUOTE && \
			data->input.tokens->type == ARG && \
			*(data->input.tokens->token) == '~')
		{
			tmp = str_replace(data->input.tokens->token, "~", \
				get_envp_var(data->envp, "HOME="));
			free(data->input.tokens->token);
			data->input.tokens->token = tmp;
		}
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = token_head;
}
