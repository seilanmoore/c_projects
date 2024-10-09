/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:01:27 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/09 16:59:33 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_dir(char *path)
{
	char	*dir;
	int		len;

	dir = ft_strrchr(path, '/');
	if (!dir)
		return (ft_strdup(path));
	len = dir - path;
	dir = ft_substr(path, 0, len);
	return (dir);
}

static char	*get_dirs(char *path, char *ptr)
{
	char	*dir;
	int		len;

	if (ptr)
	{
		dir = ft_strchr(ptr, '/');
		if (!dir)
			return (ft_strdup(path));
		len = dir - path;
		dir = ft_substr(path, 0, len);
		return (dir);
	}
	return (NULL);
}

int	dir_f_checks(char *path)
{
	char	*dir;
	char	*ptr;

	ptr = path;
	if (path[0] == '/')
		ptr++;
	dir = get_dirs(path, ptr);
	printf("dir: \"%s\"\n", dir);
	while (dir && !g_signal)
	{
		printf("dir: \"%s\"\n", dir);
		if (access(dir, F_OK) == -1)
		{
			free(dir);
			ft_putstr_fd(MS, 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": " PATH_EXIST, 2);
			return (1);
		}
		if (access(dir, R_OK) == -1)
		{
			free(dir);
			ft_putstr_fd(MS, 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": " PERMIT, 2);
			return (1);
		}
		ptr = path + ft_strlen(dir);
		printf("ptr: %s\n", ptr);
		if (ptr && !(*ptr))
			ptr = NULL;
		else
			ptr++;
		free (dir);
		dir = get_dirs(path, ptr);
	}
	return (0);
}

int	dir_f_check(char *path)
{
	char	*dir;

	dir = get_dir(path);
	if (!dir)
		return (1);
	if (access(dir, F_OK) == -1)
	{
		free(dir);
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": " PATH_EXIST, 2);
		return (1);
	}
	free(dir);
	return (0);
}

int	dir_r_check(char *path)
{
	char	*dir;

	dir = get_dir(path);
	if (!dir)
		return (1);
	if (access(dir, R_OK) == -1)
	{
		free(dir);
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": " PERMIT, 2);
		return (1);
	}
	free(dir);
	return (0);
}

int	dir_w_check(char *path)
{
	char	*dir;

	dir = get_dir(path);
	if (!dir)
		return (1);
	if (access(dir, W_OK) == -1)
	{
		free(dir);
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": " PERMIT, 2);
		return (1);
	}
	free(dir);
	return (0);
}
