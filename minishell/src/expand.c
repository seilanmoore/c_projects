/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/22 16:00:03 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* static void	expand_home(t_data *data, char **ptr, int *i)
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
		*i = *i + ft_strlen(identifier);
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
} */

void	free_lst(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		free((*lst)->content);
		(*lst)->content = NULL;
		*lst = (*lst)->next;
		free(tmp);
	}
}

void	print_list(t_list *lst)
{
	int	i;

	i = 1;
	while (lst)
	{
		printf("String (%d): /%s/\n", i++, (char *)lst->content);
		lst = lst->next;
	}
}

void	add_terms(t_list **lst, char *str, int *i, int *j)
{
	if (str[*i] == '\'')
	{
		*j = *i;
		while (str[++(*i)] && str[*i] != '\'')
			;
		ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, *i - *j + 1)));
		*j = *i + 1;
	}
	else if (str[*i] == '\"')
	{
		*j = *i;
		while (str[++(*i)] && str[*i] != '\"')
			;
		ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, *i - *j + 1)));
		*j = *i + 1;
	}
	else if (!str[*i + 1] || \
	(str[*i + 1] && (str[*i + 1] == '\'' || str[*i + 1] == '\"')))
		ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, *i - *j + 1)));
	if (str[*i])
		(*i)++;
}

t_list	*split_terms(t_data *data)
{
	t_list	*lst;
	char	*str;
	int		i;
	int		start;

	str = data->input.raw_line;
	i = 0;
	start = 0;
	lst = NULL;
	while (str[i])
		add_terms(&lst, str, &i, &start);
	return (lst);
}

void	replace_dollar(t_data *data, char **new_term)
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

char	*seek_replace(t_data *data, char *term, t_list *next)
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
			if (*next_to || next)//&& \
			//(*next_to == '$' || *next_to == '?' || valid_char(*next_to)))
				replace_dollar(data, &new_term);
			else
				dollar = NULL;
		}
	}
	return (new_term);
}

void	expand_terms(t_data *data, t_list **lst)
{
	t_list	*head;
	char	*new_term;

	head = *lst;
	while ((*lst))
	{
		//printf("String: /%s/\n", (char *)(*lst)->content);
		if (*(char *)(*lst)->content != '\'')
		{
			if ((*lst)->next)
				new_term = seek_replace(data, (char *)(*lst)->content, ((*lst)->next));
			else
				new_term = seek_replace(data, (char *)(*lst)->content, NULL);
			free((*lst)->content);
			(*lst)->content = new_term;
		}
		(*lst) = (*lst)->next;
	}
	*lst = head;
}

char	*lst_str_join(t_list *lst)
{
	char	*joined;
	char	*tmp;

	joined = ft_strdup((char *)lst->content);
	lst = lst->next;
	while (lst)
	{
		tmp = joined;
		joined = ft_strjoin(joined, (char *)lst->content);
		free(tmp);
		lst = lst->next;
	}
	return (joined);
}

void	expand(t_data *data)
{
	t_list	*lst;

	lst = split_terms(data);
	expand_terms(data, &lst);
	free(data->input.raw_line);
	data->input.raw_line = lst_str_join(lst);
	free_lst(&lst);
	//printf("Expanded raw line: %s\n", data->input.raw_line);
}
