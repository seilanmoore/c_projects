/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:37:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/09 17:42:54 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_ms_wild(char *wildcard)
{
	ft_putstr_fd(MS, 2);
	ft_putstr_fd(wildcard, 2);
}

int	handle_errno(char *wildcard)
{
	if (errno == ENOTDIR)
	{
		print_ms_wild(wildcard);
		ft_putendl_fd(": " NOT_DIR, 2);
		return (1);
	}
	if (errno == EISDIR)
	{
		print_ms_wild(wildcard);
		ft_putendl_fd(": " IS_DIR, 2);
		return (1);
	}
	if (errno == EACCES)
	{
		print_ms_wild(wildcard);
		ft_putendl_fd(": " PERMIT, 2);
		return (1);
	}
	if (errno == ENOENT)
	{
		print_ms_wild(wildcard);
		ft_putendl_fd(": " PATH_EXIST, 2);
		return (1);
	}
	return (0);
}
