/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:42:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/05 17:53:46 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

	len = ft_strrchr(data->argv[4], '/') - data->argv[4] + 1;
	tmp = ft_substr(data->argv[4], 0, len);
	if (access(tmp, F_OK) != ERROR && access(tmp, W_OK) == ERROR)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (access(data->argv[4], F_OK) != ERROR
		&& access(data->argv[4], W_OK) == ERROR)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->argv[4], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	free(tmp);
}

void	check_permissions(t_data *data)
{
	check_infile(data);
	check_outfile(data);
}
