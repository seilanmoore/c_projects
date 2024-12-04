/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 10:18:49 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
replace_dollar

Reemplaza una variable $ en un término con su valor
correspondiente (de las variables de entorno o locales). Utiliza funciones
auxiliares para obtener el valor y concatenarlo.
*/

void	replace_dollar(t_data *data, char **new_term)
{
	char		*identifier;
	char		*value;
	char		*value_quoted;
	char		*tmp;

	identifier = extract_id(*new_term);
	value = ft_strjoin("\"", get_dollar_value(data, identifier + 1));
	value_quoted = ft_strjoin(value, "\"");
	free(value);
	tmp = *new_term;
	*new_term = str_replace(*new_term, identifier, value_quoted);
	free(identifier);
	free(tmp);
	free(value_quoted);
}

/*
seek_replace

Busca dentro de una cadena términos con el prefijo $ y
llama a replace_dollar si encuentra variables válidas.
*/

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
			if ((*next_to && \
			(*next_to == '$' || *next_to == '?' || valid_char(*next_to))) \
			|| (!(*next_to) && next))
				replace_dollar(data, &new_term);
			else
				dollar = NULL;
		}
	}
	return (new_term);
}

/*
expand_terms

Recorre una lista enlazada y aplica seek_replace en cada nodo,
expandiendo todas las variables.
*/

void	expand_terms(t_data *data, t_list **lst)
{
	t_list	*head;
	char	*new_term;

	head = *lst;
	while ((*lst))
	{
		if (*(char *)(*lst)->content != '\'')
		{
			new_term = seek_replace(
					data, (char *)(*lst)->content, ((*lst)->next));
			free((*lst)->content);
			(*lst)->content = new_term;
		}
		(*lst) = (*lst)->next;
	}
	*lst = head;
}

/*
lst_str_join

Une los elementos de una lista enlazada en una
sola cadena, útil para reconstruir la línea de entrada expandida.
*/

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

/*
expand

Función principal que realiza todo el proceso de
expansión: divide la línea de entrada en términos, aplica las
expansiones y la reconstruye.
*/

void	expand(t_data *data)
{
	t_list	*lst;

	lst = split_terms(data->input.raw_line);
	expand_terms(data, &lst);
	free(data->input.raw_line);
	data->input.raw_line = lst_str_join(lst);
	free_lst(&lst);
}

/*
Este archivo se encarga principalmente de realizar la expansión de variables
como $VAR, $$, y $? dentro de una línea de entrada del usuario
*/
