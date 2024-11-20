/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_later.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:32:03 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/09 14:04:32 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	replace_dollar_2(t_data *data, char **new_term)
{
	char		*identifier;
	char		*value;
	char		*tmp;

	identifier = extract_id(*new_term);
	value = get_dollar_value(data, identifier + 1);
	tmp = *new_term;
	*new_term = str_replace(*new_term, identifier, value);
	free(identifier);
	free(tmp);
}

static char	*seek_replace_2(t_data *data, char *term, t_list *next)
{
	char	*new_term;
	char	*dollar;
	char	*next_to;

	new_term = ft_strdup(term);
	dollar = term;
	while (dollar)
	{
		dollar = ft_strchr(new_term, '$');
		if (dollar)
		{
			next_to = dollar + 1;
			if ((*next_to && \
			(*next_to == '$' || *next_to == '?' || valid_char(*next_to))) \
			|| (!(*next_to) && next))
				replace_dollar_2(data, &new_term);
			else
				dollar = NULL;
		}
	}
	return (new_term);
}

static void	expand_terms_2(t_data *data, t_list **lst)
{
	t_list	*head;
	char	*new_term;

	head = *lst;
	while ((*lst))
	{
		if (*(char *)(*lst)->content != '\'')
		{
			new_term = seek_replace_2(
					data, (char *)(*lst)->content, ((*lst)->next));
			free((*lst)->content);
			(*lst)->content = new_term;
		}
		(*lst) = (*lst)->next;
	}
	*lst = head;
}

void	expand_later(t_data *data, char **line)
{
	t_list	*lst;

	lst = split_terms(*line);
	expand_terms_2(data, &lst);
	free(*line);
	*line = lst_str_join(lst);
	free_lst(&lst);
}
