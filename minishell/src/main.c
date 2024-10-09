/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/09 19:28:22 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile int	g_signal = 0;

void	handle_signal(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_eof(t_data *data)
{
	if (!data->input.raw_line)
		exit_builtin(data);
}

void	get_history(void)
{
	char	*ms_history;

	ms_history = ft_strjoin(getenv("HOME"), "/.ms_history");
	if (ms_history)
	{
		read_history(ms_history);
		free(ms_history);
	}
}

void	save_history(void)
{
	char	*ms_history;

	ms_history = ft_strjoin(getenv("HOME"), "/.ms_history");
	if (ms_history)
	{
		write_history(ms_history);
		free(ms_history);
	}
}

char	*prompter(t_data *data)
{
	char	*prompt;
	char	*tmp;
	char	*short_cwd;

	data->user = getenv("USER");
	tmp = ft_strjoin("[", data->user);
	prompt = ft_strjoin(tmp, ": ");
	free (tmp);
	data->cwd = getcwd(NULL, 0);
	short_cwd = cwd_compress(data);
	if (short_cwd)
	{
		tmp = ft_strjoin(prompt, short_cwd);
		free(short_cwd);
	}
	else
		tmp = ft_strjoin(prompt, data->cwd);
	free(prompt);
	data->prompt = ft_strjoin(tmp, "]$ ");
	free(tmp);
	return (data->prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	init_data(&data, argc, argv, envp);
	get_history();
	while (1)
	{
		data.input.raw_line = readline(prompter(&data));
		handle_eof(&data);
		if (data.input.raw_line && ft_strlen(data.input.raw_line) > 0)
		{
			data.history = ft_strtrim(data.input.raw_line, "\n");
			if (data.history && ft_strlen(data.history) > 0)
				add_history(data.history);
			save_history();
			parser(&data);
			execute(&data);
			free(data.prev_exit_code);
			data.prev_exit_code = ft_itoa(data.exit_code);
		}
		free_data(&data);
	}
	exit(0);
}
