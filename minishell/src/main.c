/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/12 15:03:59 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal;

void	handle_quit(int sig)
{
	(void)sig;
	g_signal = 131;
	ft_putendl_fd("Quit (core dumped)", 2);
}

void	handle_signal(int sig)
{
	(void)sig;
	if (g_signal)
	{
		write(1, "\n", 1);
		kill(g_signal, SIGINT);
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_signal = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	init_data(&data, envp);
	get_history();
	while (1)
		minishell(&data);
	exit(0);
}
