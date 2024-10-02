/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:47:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/02 13:48:53 by smoore-a         ###   ########.fr       */
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

int	echo_builtin(t_data *data, t_tokens *token, int fd)
{
	t_tokens	*arg;

	if (token->opt)
	{
		if ((token->opt->next && token->opt->next->type == OPTION) || \
		ft_strlen(token->opt->token) > 2)
			return (print_msg(data, MS ECHO ECHO_OPTS, -1), 1);
		if (token->opt->token[1] != 'n')
			return (print_msg(data, MS ECHO ECHO_OPT, -1), 1);
		else
		{
			arg = token->arg;
			while (arg && arg->type == ARG)
			{
				print_arg(arg->token, fd);
				arg = arg->next;
				if (arg && arg->type == ARG)
					ft_putchar_fd(' ', fd);
			}
			return (0);
		}
	}
	arg = token->arg;
	while (arg && arg->type == ARG)
	{
		print_arg(arg->token, fd);
		arg = arg->next;
		if (arg && arg->type == ARG)
			ft_putchar_fd(' ', fd);
	}
	ft_putchar_fd('\n', fd);
	return (0);
}
