/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:50:58 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/12 13:30:46 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	contain_digit(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

static void	several_args(char **args, int *exit_)
{
	int	i;

	i = 0;
	while (args[++i])
		;
	if (i > 2)
	{
		*exit_ = 1;
		ft_putendl_fd(MS "exit: too many arguments", 2);
	}
	else if (args[1])
		*exit_ = ft_atoi(args[1]);
}

static int	not_valid_arg(char **args, int *exit_)
{
	if (args[1])
	{
		if (contain_digit(args[1]))
			*exit_ = ft_atoi(args[1]);
		else
		{
			*exit_ = 2;
			ft_putstr_fd(MS "exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (0);
		}
	}
	return (1);
}

int	exit_builtin(t_data *data, t_cmd *cmd)
{
	char	**args;
	int		exit_;

	exit_ = -1;
	args = NULL;
	ft_putendl_fd("exit", 1);
	if (cmd)
	{
		args = cmd->args;
		if (not_valid_arg(args, &exit_))
			several_args(args, &exit_);
	}
	ft_free(&(data->process));
	ft_free(&(data->prev_exit_code));
	free_local(data);
	free_environment(data);
	free_data(data);
	rl_clear_history();
	clear_history();
	if (exit_ != -1)
		exit(exit_);
	exit(EXIT_SUCCESS);
}
