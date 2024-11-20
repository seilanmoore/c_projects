/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:54:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/02 17:15:44 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	valid_ident(char *str)
{
	if (!str)
		return (1);
	if (*str == '\0')
		return (0);
	if (ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (*str != '_' && *str != '$' && (*str < 'a' || *str > 'z') && \
			(*str < 'A' || *str > 'Z') && (*str < '0' || *str > '9'))
			return (0);
		str++;
	}
	return (1);
}

char	**split_token(char *token)
{
	char	**array;
	int		i;

	array = ft_calloc(3, sizeof(char *));
	i = -1;
	if (token[0] == '=')
	{
		array[0] = ft_strdup(token);
		return (array);
	}
	while (token[++i])
	{
		if (token[i] == '=')
		{
			array[0] = ft_substr(token, 0, i);
			array[1] = ft_strdup(&token[++i]);
			return (array);
		}
	}
	return (NULL);
}

char	*rev_split(char **array)
{
	char	*str;
	char	*prev_str;
	char	*aux;
	int		i;

	i = 0;
	str = ft_strdup(array[i]);
	while (array[++i])
	{
		prev_str = str;
		aux = ft_strjoin(str, " ");
		str = ft_strjoin(aux, array[i]);
		free(aux);
		free(prev_str);
		if (!str)
			break ;
	}
	return (str);
}

char	*get_envp_var(char **envp, char *var)
{
	int	v_len;
	int	i;

	if (!envp)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		v_len = ft_strchr(envp[i], '=') - envp[i];
		if (!ft_strncmp(envp[i], var, v_len))
		{
			if (ft_strlen(var) == (size_t)v_len)
				return (ft_strchr(envp[i], '=') + 1);
		}
	}
	return (NULL);
}
