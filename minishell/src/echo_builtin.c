/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:47:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/14 14:34:45 by smoore-a         ###   ########.fr       */
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

int	next_opt(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == OPTION)
			return (1);
	}
	return (0);
}

static int	next_arg(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == ARG)
			return (1);
	}
	return (0);
}

static int	check_options(t_data *data, t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == OPTION)
		{
			if (ft_strlen(token->token) > 2 || next_opt(token))
				return (print_msg(data, MS ECHO ECHO_OPTS, -1), 1);
			if (token->token[1] != 'n')
				return (print_msg(data, MS ECHO ECHO_OPT, -1), 1);
			token = token->next;
			while (token && token->type != PIPE)
			{
				if (token->type == ARG)
				{
					print_arg(token->token);
					if (token->token && *(token->token) && \
					token->next && token->next->type == ARG)
						ft_putchar_fd(' ', 1);
				}
				token = token->next;
			}
			return (2);
		}
		token = token->next;
	}
	return (0);
}

int	echo_builtin(t_data *data, t_token *token)
{
	int	options;

	options = check_options(data, token);
	if (options == 1)
		return (1);
	if (!options)
	{
		while (token && token->type != PIPE)
		{
			if (token->type == ARG)
			{
				print_arg(token->token);
				if (next_arg(token))
					ft_putchar_fd(' ', 1);
			}
			token = token->next;
		}
		ft_putchar_fd('\n', 1);
	}
	return (0);
}
