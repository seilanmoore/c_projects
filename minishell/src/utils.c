/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:54:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/02 17:15:44 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	if (!str1 || !str2)
		return (1);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (1);
	i = -1;
	while (str1[++i])
	{
		if (str1[i] != str2[i])
			return (1);
	}
	return (0);
}

int	no_word(int c)
{
	if (c == '<' || \
	c == '>' || \
	c == '|')
		return (1);
	return (0);
}

int	is_redir(int c)
{
	if (c == LEFT || \
	c == LEFTT || \
	c == RIGHT || \
	c == RIGHTT)
		return (1);
	return (0);
}

int	is_space(int c)
{
	if (c && (\
	c == ' ' || \
	c == '\t' || \
	c == '\n' || \
	c == '\r' || \
	c == '\f' || \
	c == '\v'))
		return (1);
	return (0);
}

int	is_cmd(int c)
{
	if (c && (\
	(c >= 'a' && c <= 'z') || \
	(c >= 'A' && c <= 'Z') || \
	(c >= '0' && c <= '9') || \
	c == '$' || \
	c == '*' || \
	c == '/' || \
	c == '.' || \
	c == '-' || \
	c == '_' || \
	c == '\\'))
		return (1);
	return (0);
}

char	*cwd_compress(t_data *data)
{
	char	*short_cwd;
	char	*home;

	short_cwd = NULL;
	if (!data->envp)
		home = getenv("HOME");
	else
		home = get_envp_var(data->envp, "HOME");
	if (!ft_strncmp(data->cwd, home, ft_strlen(home)))
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
	{
		ft_putstr_fd(array[i], 2);
		if (array[i + 1])
			ft_putstr_fd(" ", 2);
	}
}

char	*type_to_char(int type)
{
	if (type == CMD)
		return ("CMD");
	if (type == OPTION)
		return ("OPTION");
	if (type == ARG)
		return ("ARGUMENT");
	if (type == PIPE)
		return ("PIPE");
	if (type == LEFT)
		return ("<");
	if (type == RIGHT)
		return (">");
	if (type == LEFTT)
		return ("<<");
	if (type == RIGHTT)
		return (">>");
	if (type == FILE)
		return ("FILE");
	if (type == HERE)
		return ("HEREDOC");
	if (type == LOCAL)
		return ("LOCAL");
	if (type == LOCAL_VAL)
		return ("VALUE");
	return ("NO_TYPE");
}

void	print_types(t_data *data)
{
	t_token	*head;
	t_token	*aux;

	head = data->input.tokens;
	while (head)
	{
		printf("TOKEN: \"%s\"	TYPE: %s(%d)	END_SPACE: %d\n", \
		head->token, type_to_char(head->type), head->type, head->end_space);
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

void	print_cmd_array(t_data *data)
{
	t_cmd	*head;

	head = data->input.command;
	while (head)
	{
		printf("CMD_PATH: \"%s\" ARGUMENTS: ", head->cmd);
		print_array(head->args);
		printf("\n");
		head = head->next;
	}
}

int	valid_char(char c)
{
	if (!c)
		return (0);
	if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && \
	(c < '0' || c > '9') && c != '_')
		return (0);
	return (1);
}

int	valid_ident(char *str)
{
	if (!str)
		return (1);
	if (*str == '\0')
		return (0);
	if (ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (*str != '_' && *str != '$' && (*str < 'a' || *str > 'z') && \
			(*str < 'A' || *str > 'Z') && (*str < '0' || *str > '9'))
			return (0);
		str++;
	}
	return (1);
}

char	**split_token(char *token)
{
	char	**array;
	int		i;

	array = ft_calloc(3, sizeof(char *));
	i = -1;
	if (token[0] == '=')
	{
		array[0] = ft_strdup(token);
		return (array);
	}
	while (token[++i])
	{
		if (token[i] == '=')
		{
			array[0] = ft_substr(token, 0, i);
			array[1] = ft_strdup(&token[++i]);
			return (array);
		}
	}
	return (NULL);
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
	int	v_len;
	int	i;

	if (!envp)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		v_len = ft_strchr(envp[i], '=') - envp[i];
		if (!ft_strncmp(envp[i], var, v_len))
		{
			if (ft_strlen(var) == (size_t)v_len)
				return (ft_strchr(envp[i], '=') + 1);
		}
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
