/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:47:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/05 15:07:40 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_arg(char *arg)
{
	if (!arg)
		return ;
	while (*arg)
	{
		if (*arg != '\\')
			write(1, &(*arg), 1);
		arg++;
		if (*arg && *arg != '\"' && *(arg - 1) == '\\')
			write(1, "\\", 1);
	}
}

static int	check_options(t_data *data, t_token *token)
{
	t_token	*arg;

	if ((token->opt->next && token->opt->next->type == OPTION) || \
	ft_strlen(token->opt->token) > 2)
		return (print_msg(data, MS ECHO ECHO_OPTS, -1), 1);
	if (token->opt->token[1] != 'n')
		return (print_msg(data, MS ECHO ECHO_OPT, -1), 1);
	arg = token->arg;
	while (arg && arg->type == ARG)
	{
		print_arg(arg->token);
		if (arg->token && *(arg->token) && \
		arg->next && arg->next->type == ARG)
			ft_putchar_fd(' ', 1);
		arg = arg->next;
	}
	return (0);
}

int	echo_builtin(t_data *data, t_token *token)
{
	t_token	*arg;

	if (token->opt)
	{
		if (check_options(data, token) == 1)
			return (1);
	}
	else
	{
		arg = token->arg;
		while (arg && arg->type == ARG)
		{
			print_arg(arg->token);
			if (arg->token && *(arg->token) && \
			arg->next && arg->next->type == ARG)
				ft_putchar_fd(' ', 1);
			arg = arg->next;
		}
		ft_putchar_fd('\n', 1);
	}
	return (0);
}
