/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:15:47 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/22 13:24:51 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_dollar_value(t_data *data, char *variable)
{
	t_env	*env_var;
	t_env	*local_head;

	if (!variable)
		return (NULL);
	if (*variable == '\0')
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
	if (len == 1)
		return (ft_strdup("$"));
	return (ft_substr(identifier, 0, len));
}
