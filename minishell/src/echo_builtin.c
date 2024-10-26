/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:47:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/26 15:40:23 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_option(char **args)
{
	int	i;

	if (ft_strcmp(args[1], "-n"))
		return (0);
	i = 1;
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
	}
	return (1);
}

int	echo_builtin(t_cmd *cmd)
{
	char	**args;
	int		i;

	args = cmd->args;
	if (check_option(args))
		return (0);
	i = 0;
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
	return (0);
}
