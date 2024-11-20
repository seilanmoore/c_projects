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
