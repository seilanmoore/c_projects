/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/12 14:31:59 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	update_token(t_data *data, t_token *token, char **ptr)
{
	char		*identifier;
	char		*value;
	char		*tmp;

	if (**ptr == '$' && *ptr + 1 && \
	(*(*ptr + 1) == '$' || *(*ptr + 1) == '?' || valid_char(*(*ptr + 1))))
	{
		tmp = token->token;
		identifier = extract_id(*ptr);
		value = get_dollar_value(data, identifier + 1);
		token->token = str_replace(token->token, identifier, value);
		free(identifier);
		free(tmp);
	}
	(*ptr)++;
	if (*ptr && **ptr == '$' && *(*ptr - 1) == '$')
		(*ptr)++;

}

static void	check_token(t_data *data, char *aux)
{
	t_token	*token;
	char	*ptr;

	token = data->input.tokens;
	ptr = ft_strdup(token->token);
	aux = ptr;
	update_token(data, token, &ptr);
	while (ptr && *ptr)
	{
		if (*(ptr - 1) != '\\')
			update_token(data, token, &ptr);
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
	t_token	*token_head;
	char	*aux;

	token_head = data->input.tokens;
	while (data->input.tokens)
	{
		if (data->input.tokens->quote != S_QUOTE && \
		data->input.tokens->token && \
		*(data->input.tokens->token))
		{
			aux = NULL;
			check_token(data, aux);
			expand_home(data);
		}
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = token_head;
}
