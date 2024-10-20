/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/19 21:41:56 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	expand_home(t_data *data, char **ptr, int *i)
{
	char	*value;
	char	*tmp;
	char	*pre;

	value = get_envp_var(data->envp, "HOME");
	if (value)
	{
		pre = ft_substr(data->input.raw_line, 0, *i);
		tmp = ft_strjoin(pre, value);
		free(pre);
		pre = data->input.raw_line;
		data->input.raw_line = ft_strjoin(tmp, *ptr + 1);
		free(tmp);
		free(pre);
	}
}

// $var0$hola"adios $var" var1$var2$var3$

static void	update_token(t_data *data, char **ptr, int *i)
{
	char		*identifier;
	char		*value;
	char		*tmp;
	char		*pre;

	if ((*ptr) + 1 && \
	(*((*ptr) + 1) == '$' || *((*ptr) + 1) == '?' || valid_char(*((*ptr) + 1))))
	{
		identifier = extract_id(*ptr);
		value = get_dollar_value(data, identifier + 1);
		pre = ft_substr(data->input.raw_line, 0, *i);
		tmp = ft_strjoin(pre, value);
		free(pre);
		pre = data->input.raw_line;
		data->input.raw_line = ft_strjoin(tmp, *ptr + ft_strlen(identifier));
		free(tmp);
		free(pre);
		free(identifier);
		*ptr = *ptr + ft_strlen(identifier);
		if (**ptr == '$' && (*ptr) + 1 && (*((*ptr) + 1) == '$'))
		{
			(*ptr)++;
			(*i)++;
		}
	}
}

static void	check_char(t_data *data, char **ptr, int *i)
{
	if (**ptr == '~' && is_space(*((*ptr) - 1)))
		expand_home(data, ptr, i);
	if (*((*ptr) - 1) != '\\' && **ptr == '$')
		update_token(data, ptr, i);
}

// $var0$hola"adios $var" var1$var2$var3$

void	expand(t_data *data)
{
	char	*ptr;
	char	*tmp;
	int		in_quote;
	int		i;

	ptr = ft_strdup(data->input.raw_line);
	tmp = ptr;
	i = 0;
	if (*ptr == '~')
		expand_home(data, &(ptr), 0);
	else if (*ptr == '$')
		update_token(data, &(ptr), 0);
	ptr++;
	i++;
	while (*ptr)
	{
		if (*ptr == '\'' && in_quote == 0)
			in_quote = 1;
		else
			in_quote = 0;
		if (!in_quote)
			check_char(data, &ptr, &i);
		i++;
		ptr++;
	}
	free (tmp);
}
