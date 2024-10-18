/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/18 16:56:22 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	update_token(t_data *data, char **ptr)
{
	char		*identifier;
	char		*value;
	char		*tmp;

	if (**ptr == '$' && *ptr + 1 && \
	(*(*ptr + 1) == '$' || *(*ptr + 1) == '?' || valid_char(*(*ptr + 1))))
	{
		tmp = data->input.raw_line;
		identifier = extract_id(*ptr);
		value = get_dollar_value(data, identifier + 1);
		data->input.raw_line = str_replace(data->input.raw_line, identifier, value);
		free(identifier);
		free(tmp);
	}
	(*ptr)++;
	if (*ptr && **ptr == '$' && *(*ptr - 1) == '$')
		(*ptr)++;
}

static void	check_token(t_data *data, char *aux, char *raw_pos)
{
	char	*ptr;

	ptr = ft_strdup(raw_pos);
	aux = ptr;
	update_token(data, &ptr);
	while (ptr && *ptr)
	{
		if (*(ptr - 1) != '\\')
			update_token(data, &ptr);
		else
		{
			ptr++;
			if (ptr && *ptr == '$' && *(ptr - 1) == '$')
				ptr++;
		}
	}
	free(aux);
}

void	expand(t_data *data)
{
	char	*aux;
	int		in_quote;
	int		i;

	i = -1;
	while (data->input.raw_line[++i])
	{
		if (data->input.raw_line[i] == '\'' && in_quote == 0)
			in_quote = 1;
		else
			in_quote = 0;
		if (!in_quote)
		{
			aux = NULL;
			check_token(data, aux, &(data->input.raw_line[i]));
			//expand_home(data);
		}
	}
}
