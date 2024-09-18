/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/07/22 19:45:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	*data = (t_data){0};
	data->input = (t_input){0};
	data->envp = envp;
	data->argc = argc;
	data->argv = argv;
}

void	free_mtrx(char **mtrx)
{
	int	i;

	i = -1;
	if (!mtrx)
		return ;
	while (mtrx[++i])
		free(mtrx[i]);
	free(mtrx);
}

void	free_data(t_data *data)
{
	int	i;

	free(data->prompt);
	free(data->input.raw_line);
	i = -1;
	if (data->input.tokens)
	{
		while (data->input.tokens[++i].token)
			free(data->input.tokens[i].token);
		free(data->input.tokens);
	}
	i = -1;
	if (data->input.command)
	{
		while (data->input.command[++i].cmd)
			free(data->input.command[i].cmd);
		free(data->input.command);
	}
	free_mtrx(data->paths);
	init_data(data, data->argc, data->argv, data->envp);
}

void signal_handler(int sig) {
    if (sig == SIGINT) {
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
	while (1)
	{
		data.input.raw_line = readline(prompter(&data));
		if (!data.input.raw_line)
		{
			write(1, GREEN "exit" WHITE "\n" WHITE, 14);
			free_data(&data);
			break;
		}
        add_history(data.input.raw_line);
		parse(&data);
		free_data(&data);
	}
	write_history(HISTORY_FILE);
	rl_clear_history();
	clear_history();
	exit(EXIT_SUCCESS);
}
