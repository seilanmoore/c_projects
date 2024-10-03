/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/03 10:20:17 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	expand_home(t_data *data)
{
	char	*value;
	char	*tmp;

	if (data->input.tokens->token && \
		data->input.tokens->quote == NO_QUOTE && \
		data->input.tokens->type == ARG && \
		*(data->input.tokens->token) == '~')
	{
		value = get_envp_var(data->envp_cpy, "HOME=");
		if (!value)
			value = get_envp_var(data->envp, "HOME=");
		tmp = str_replace(data->input.tokens->token, "~", value);
		free(data->input.tokens->token);
		data->input.tokens->token = tmp;
	}
}

static char	*get_dollar_value(t_data *data, char *variable)
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

static char	*extract_id(char *token)
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

static void	check_token(t_data *data, char *tmp, char *aux)
{
	t_tokens	*token;
	char		*identifier;
	char		*value;
	char		*ptr;

	token = data->input.tokens;
	ptr = ft_strdup(token->token);
	aux = ptr;
	if (*ptr == '$' && ptr + 1 && *(ptr + 1))
	{
		tmp = token->token;
		identifier = extract_id(ptr);
		value = get_dollar_value(data, identifier + 1);
		token->token = str_replace(token->token, identifier, value);
		free(identifier);
		free(tmp);
	}
	ptr++;
	if (ptr && *ptr == '$' && *(ptr - 1) == '$')
		ptr++;
	while (ptr && *ptr && !g_signal)
	{
		if (*ptr == '$' && ptr + 1 && *(ptr + 1) && *(ptr - 1) != '\\')
		{
			tmp = token->token;
			identifier = extract_id(ptr);
			value = get_dollar_value(data, identifier + 1);
			token->token = str_replace(token->token, identifier, value);
			free(identifier);
			free(tmp);
		}
		ptr++;
		if (ptr && *ptr == '$' && *(ptr - 1) == '$')
			ptr++;
	}
	free(aux);
}

void	expand(t_data *data)
{
	t_tokens	*token_head;
	char		*tmp;
	char		*aux;

	token_head = data->input.tokens;
	while (data->input.tokens && !g_signal)
	{
		if (data->input.tokens->quote != S_QUOTE)
		{
			tmp = NULL;
			aux = NULL;
			check_token(data, tmp, aux);
			expand_home(data);
		}
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = token_head;
}
