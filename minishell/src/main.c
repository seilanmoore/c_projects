/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/25 11:02:54 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

void	print_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		printf("%s\n", array[i]);
}

void	handle_eof(t_data *data)
{
	if (!data->input.raw_line)
		exit_builtin(data);
}

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*prompter(t_data *data)
{
	char	*prompt;
	char	*tmp;

	data->user = getenv("USER");
	data->cwd = getcwd(NULL, 0);
	prompt = NULL;
	tmp = NULL;
	prompt = ft_strjoin(data->user, ": ");
	tmp = ft_strjoin(prompt, data->cwd);
	free(prompt);
	free(data->cwd);
	data->prompt = ft_strjoin(tmp, " $ ");
	free(tmp);
	return (data->prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_data(&data, argc, argv, envp);
	signal(SIGINT, signal_handler);
	read_history(HISTORY_FILE);
	while (data.status == -1)
	{
		data.input.raw_line = readline(prompter(&data));
		handle_eof(&data);
		if (data.input.raw_line && ft_strlen(data.input.raw_line) > 0)
		{
			data.history = ft_strtrim(data.input.raw_line, "\n");
			if (data.history && ft_strlen(data.history) > 0)
				add_history(data.history);
			write_history(HISTORY_FILE);
			parser(&data);
		}
		free_data(&data);
	}
	rl_clear_history();
	exit(data.status);
}
