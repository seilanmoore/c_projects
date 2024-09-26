/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/26 14:54:51 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <bits/types/struct_itimerspec.h>


char	*get_dollar_value(t_data *data, char *variable)
{
	t_environment	*env_var;
	t_l_variable	*local_head;

	if (!variable)
		return (NULL);
	if (!ft_strncmp(variable, "$", ft_strlen(variable)))
		return (data->process);
	env_var = get_env_var(data->env, variable);
	if (env_var)
		return (env_var->value);
	local_head = get_l_var(data->local, variable);
	if (local_head)
		return (local_head->value);
	return (NULL);
}

//terminar implementacion de expansion de variables

void	replace_dollar(t_data *data)
{
	char	*token;
	char	**tmp;
	int		i;
	char	*dollar_value;
	char	*aux;

	token = data->input.tokens->token;
	if (!ft_strncmp(token, "", 1))
		return ;
	tmp = ft_split(data->input.tokens->token, ' ');
	i = -1;
	(void)dollar_value;
	while (tmp[++i])
	{
		if (ft_strrchr(tmp[i], '$') && ft_strlen(tmp[i]) > 1 && !ft_strnstr(tmp[i], "\\$", 2))
		{
			dollar_value = get_dollar_value(data, ft_strrchr(tmp[i], '$') + 1);
			aux = tmp[i];
			free(aux);
		}
	}
	data->input.tokens->token = rev_split(tmp);
	free(token);
	free_array(tmp);
}

/* void	check_dollar(t_data *data)
{

} */

char	*extract_id(char *token)
{
	char	*identfier;
	int		len;

	identfier = ft_strchr(token, '$') + 1;
	len = 0;
	if (identfier[0] == '$')
		return (ft_strdup("$"));
	while (identfier[len] && identfier[len] != '$' && \
		identfier[len] != '=' && !signalize)
		len++;
	if (!len)
		return (ft_strdup(""));
	return (ft_substr(identfier, 0, len));
}

char	*replace_id(char *token, char *id, char *value)
{
	char	*str;
	char	*tmp;
	char	len;

	//printf("token:\'%s\'  id:\'%s\'  value: \'%s\'\n", token, id, value);
	printf("token: \'%s\'\n", token);
	printf("id: \'%s\'\n", id);
	len = ft_strnstr(token, id, ft_strlen(token)) - token;
	if (id && *id == '$')
		len++;
	if (len > 0)
		len--;
	str = ft_substr(token, 0, len);
	//printf("\'%s\'\n", str);
	if (!str)
		return (NULL);
	token = ft_strnstr(token, id, ft_strlen(token)) + ft_strlen(id);
	if (id && *id == '$')
		token++;
	tmp = str;
	if (value)
		str = ft_strjoin(str, value);
	else
	 	str = ft_strjoin(str, "");
	free(tmp);
	if (!str)
		return (NULL);
	tmp = str;
	str = ft_strjoin(str, token);
	if (!str)
		return (NULL);
	free(tmp);
	return (str);
}

void	expand(t_data *data)
{
	t_tokens	*token_head;
	char		*tmp;
	char		*identifier;
	char		*value;

	token_head = data->input.tokens;
	while (data->input.tokens && !signalize)
	{
		while (data->input.tokens->quote == NO_QUOTE && \
			ft_strchr(data->input.tokens->token, '$') && !signalize)
		{
			tmp = data->input.tokens->token;
			identifier = extract_id(tmp);
			value = get_dollar_value(data, identifier);
			data->input.tokens->token = replace_id(tmp, identifier, value);
			free(tmp);
			free(identifier);
		}
		/* if (data->input.tokens->quote == D_QUOTE)
			replace_dollar(data); */
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = token_head;
}
