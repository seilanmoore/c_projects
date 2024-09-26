/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:54:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/26 11:42:25 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_msg(t_data *data, char *msg, int status)
{
	ft_putendl_fd(msg, 2);
	data->status = status;
}

void	print_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		printf("%s\n", array[i]);
}

char	*type_to_char(int type)
{
	if (type == 100)
		return ("CMD");
	if (type == 101)
		return ("OPTION");
	if (type == 102)
		return ("ARGUMENT");
	if (type == 103)
		return ("PIPE");
	if (type == 104)
		return ("<");
	if (type == 105)
		return (">");
	if (type == 106)
		return ("<<");
	if (type == 107)
		return (">>");
	if (type == 108)
		return ("FILE");
	if (type == 109)
		return ("HEREDOC");
	if (type == 110)
		return ("VARIABLE");
	if (type == 111)
		return ("VALUE");
	if (type == 112)
		return ("LOCAL VARIABLE");
	if (type == 113)
		return ("LOCAL VALUE");
	if (type == 114)
		return ("SINGLE QUOTES");
	if (type == 115)
		return ("DOUBLE QUOTES");
	if (type == 116)
		return ("NO QUOTES");
	return ("NO_TYPE");
}

void	print_types(t_data *data)
{
	t_tokens	*head;

	head = data->input.tokens;
	while (head)
	{
		printf("TOKEN: \"%s\"	TYPE: %s\n", head->token, type_to_char(head->type));
		head = head->next;
	}
}

int	valid_char(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != '_' &&  *str != '$' && \
			(*str < 'A' || *str > 'Z') && (*str < '0' || *str > '9'))
			return (0);
		str++;
	}
	return (1);
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
