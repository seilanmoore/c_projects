/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:47:27 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/24 20:44:50 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*variable_append(t_token **args)
{
	char	*full_var;
	char	*tmp;
	char	*equal;

	equal = ft_strchr((*args)->token, '=');
	if (equal)
		return(ft_substr((*args)->token, 0, equal - (*args)->token));
	full_var = NULL;
	while ((*args) && (*args)->type == ARG)
	{
		equal = ft_strchr(full_var, '=');
		if ((*args)->end_space == 0 && !equal)
		{
			tmp = full_var;
			full_var = ft_strjoin(full_var, (*args)->token);
			free(tmp);
		}
		else if (equal)
		{
			tmp = full_var;
			full_var = ft_substr(full_var, 0, equal - full_var);
			free(tmp);
			return (full_var);
		}
		else
			return (free(full_var), NULL);
		(*args) = (*args)->next;
	}
	return (NULL);
}

char	*value_append(t_token **args)
{
	char	*full_val;
	char	*tmp;
	char	*equal;

	equal = ft_strchr((*args)->token, '=');
	if (equal)
	{
		full_val = ft_strdup(equal + 1);
		while ((*args) && (*args)->type == ARG)
		{
			if ((*args)->end_space == 0)
			{
				tmp = full_val;
				full_val = ft_strjoin(full_val, (*args)->token);
				free(tmp);
			}
			else
				return (full_val);
			(*args) = (*args)->next;
		}
	}
	else
	{
		full_val = ft_strdup((*args)->token);
		while ((*args) && (*args)->type == ARG)
		{
			if ((*args)->end_space == 0)
			{
				tmp = full_val;
				full_val = ft_strjoin(full_val, (*args)->token);
				free(tmp);
			}
			else
				return (full_val);
			(*args) = (*args)->next;
		}
	}
	return (NULL);
}
