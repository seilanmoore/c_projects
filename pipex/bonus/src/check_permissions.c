/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:42:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/09 13:22:24 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	check_here_doc()
{
	if (access(".here_doc", F_OK) != ERROR
		&& access(".here_doc", W_OK) == ERROR)
		unlink(".here_doc");
}

static void	check_infile(t_data *data)
{
	int		len;
	char	*tmp;

	len = ft_strrchr(data->argv[1], '/') - data->argv[1] + 1;
	tmp = ft_substr(data->argv[1], 0, len);
	if (access(tmp, F_OK) != ERROR && access(tmp, R_OK) == ERROR)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (access(data->argv[1], F_OK) != ERROR
		&& access(data->argv[1], R_OK) == ERROR)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->argv[1], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	free(tmp);
}

static void	check_outfile(t_data *data)
{
	int		len;
	char	*tmp;
	int		argn;

	argn = data->argc - 1;
	len = ft_strrchr(data->argv[argn], '/') - data->argv[argn] + 1;
	tmp = ft_substr(data->argv[argn], 0, len);
	if (access(tmp, F_OK) != ERROR && access(tmp, W_OK) == ERROR)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (access(data->argv[argn], F_OK) != ERROR
		&& access(data->argv[argn], W_OK) == ERROR)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->argv[argn], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	free(tmp);
}

void	check_permissions(t_data *data)
{
	if (ft_strncmp("here_doc", data->argv[1], ft_strlen(data->argv[1])))
		check_infile(data);
	else
	 	check_here_doc();
	check_outfile(data);
}
