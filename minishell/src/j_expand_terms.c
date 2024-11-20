/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_expand_terms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/10 21:37:46 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	d_quote_term(t_list **lst, char *str, int *i, int *j)
{
	*j = *i;
	while (str[++(*i)] && str[*i] != '\"')
		;
	ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, *i - *j + 1)));
	*j = *i + 1;
}

static void	s_quote_term(t_list **lst, char *str, int *i, int *j)
{
	*j = *i;
	while (str[++(*i)] && str[*i] != '\'')
		;
	ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, *i - *j + 1)));
	*j = *i + 1;
}

static void	dollar_term(t_list **lst, char *str, int *i, int *j)
{
	*j = *i;
	if (str[(*i) + 1] && \
	(str[(*i) + 1] == '$' || str[(*i) + 1] == '?'))
	{
		ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, 2)));
		(*i)++;
		*j = *i + 1;
	}
	else
	{
		while (str[++(*i)] && str[*i] != '$' && \
		str[*i] != '\'' && str[*i] != '\"')
			;
		ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, *i - *j)));
		if (str[*i])
			(*i)--;
		*j = *i;
	}
}

static void	add_terms(t_list **lst, char *str, int *i, int *j)
{
	if (str[*i] == '\'')
		s_quote_term(lst, str, i, j);
	else if (str[*i] == '\"')
		d_quote_term(lst, str, i, j);
	else if (str[*i] == '$')
		dollar_term(lst, str, i, j);
	else if (!str[*i + 1] || (str[*i + 1] && \
	(str[*i + 1] == '\'' || str[*i + 1] == '\"' || str[*i + 1] == '$')))
		ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, *i - *j + 1)));
	if (str[*i])
		(*i)++;
}

t_list	*split_terms(char *line)
{
	t_list	*lst;
	int		i;
	int		start;

	i = 0;
	start = 0;
	lst = NULL;
	while (line[i])
		add_terms(&lst, line, &i, &start);
	return (lst);
}
