/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:47:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/03 13:31:01 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_arg(char *arg, int fd)
{
	if (!arg || fd < 0)
		return ;
	while (*arg)
	{
		if (*arg != '\\')
			write(fd, &(*arg), 1);
		arg++;
		if (*arg && *arg != '\"' && *(arg - 1) == '\\')
			write(fd, "\\", 1);
	}
}

static int	check_options(t_data *data, t_tokens *token, int fd)
{
	t_tokens	*arg;

	if ((token->opt->next && token->opt->next->type == OPTION) || \
	ft_strlen(token->opt->token) > 2)
		return (print_msg(data, MS ECHO ECHO_OPTS, -1), 1);
	if (token->opt->token[1] != 'n')
		return (print_msg(data, MS ECHO ECHO_OPT, -1), 1);
	arg = token->arg;
	while (arg && arg->type == ARG)
	{
		print_arg(arg->token, fd);
		if (arg->token && *(arg->token) && \
		arg->next && arg->next->type == ARG)
			ft_putchar_fd(' ', fd);
		arg = arg->next;
	}
	return (0);
}

int	echo_builtin(t_data *data, t_tokens *token, int fd)
{
	t_tokens	*arg;

	if (token->opt)
	{
		if (check_options(data, token, fd) == 1)
			return (1);
	}
	else
	{
		arg = token->arg;
		while (arg && arg->type == ARG)
		{
			print_arg(arg->token, fd);
			if (arg->token && *(arg->token) && \
			arg->next && arg->next->type == ARG)
				ft_putchar_fd(' ', fd);
			arg = arg->next;
		}
		ft_putchar_fd('\n', fd);
	}
	return (0);
}
