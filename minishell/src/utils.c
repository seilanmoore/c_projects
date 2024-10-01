/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:54:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/01 14:06:53 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*cwd_compress(t_data *data)
{
	char	*short_cwd;
	char	*home;
	int		len;

	short_cwd = NULL;
	if (!data->envp_cpy)
		home = get_envp_var(data->envp, "HOME=");
	else
		home = get_envp_var(data->envp_cpy, "HOME=");
	len = ft_strlen(home);
	if (!ft_strncmp(data->cwd, home, len))
		short_cwd = str_replace(data->cwd, home, "~");
	return (short_cwd);
}

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
	t_tokens	*aux;

	head = data->input.tokens;
	while (head)
	{
		printf("TOKEN: \"%s\"	TYPE: %s\n", head->token, type_to_char(head->type));
		aux = head->opt;
		if (aux)
			printf("\t--> OPTIONS:");
		while (aux && aux->type == OPTION)
		{
			printf(" %s", aux->token);
			aux = aux->next;
		}
		printf("\n");
		aux = head->arg;
		if (aux)
			printf("\t--> ARGS:");
		while (aux && aux->type == ARG)
		{
			printf(" %s", aux->token);
			aux = aux->next;
		}
		printf("\n");
		head = head->next;
	}
}

int	valid_char(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != '_' && *str != '$' && \
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

char	*get_envp_var(char **envp, char *var)
{

	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (!ft_strncmp(*envp, var, ft_strlen(var)))
			return (ft_strchr(*envp, '=') + 1);
		envp++;
	}
	return (NULL);
}

char	*str_replace(char *haystack, char *needle, char *replace)
{
	char	*str;
	char	*ptr;
	char	*aux;
	int		len;

	if (!haystack || !needle)
		return (ft_strdup(haystack));
	ptr = ft_strnstr(haystack, needle, ft_strlen(haystack));
	len = ptr - haystack;
	str = ft_substr(haystack, 0, len);
	if (!str)
		return (NULL);
	ptr = ptr + ft_strlen(needle);
	aux = str;
	str = ft_strjoin(str, replace);
	if (!str)
		return (NULL);
	free (aux);
	aux = str;
	str = ft_strjoin(str, ptr);
	free(aux);
	if (!str)
		return (NULL);
	return (str);
}
