/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_permission.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:42:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/10 19:56:47 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	check_here_doc(void)
{
	if (access(_HERE_DOC, F_OK) != ERROR)
		unlink(_HERE_DOC);
	if (access(".", W_OK) == ERROR)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(HERE_DOC, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

static void	check_infile(t_data *data)
{
	if (access(data->argv[1], F_OK) != ERROR
		&& access(data->argv[1], R_OK) == ERROR)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(data->argv[1], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

static void	check_outfile(t_data *data)
{
	int		len;
	char	*tmp;
	int		argn;

	argn = data->argc - 1;
	len = ft_strrchr(data->argv[argn], '/') - data->argv[argn] + 1;
	if (ft_strchr(data->argv[argn], '/'))
		tmp = ft_substr(data->argv[argn], 0, len);
	else
		tmp = ft_strdup(".");
	if ((access(data->argv[argn], F_OK) != ERROR && \
		access(data->argv[argn], W_OK) == ERROR) || \
		(access(tmp, F_OK) != ERROR && access(tmp, W_OK) == ERROR))
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(data->argv[argn], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	free(tmp);
}

void	check_permission(t_data *data)
{
	if (data->here_doc_exits)
		check_here_doc();
	else
		check_infile(data);
	check_outfile(data);
}
