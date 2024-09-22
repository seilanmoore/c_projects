/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/22 14:12:00 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

void	handle_eof(t_data *data)
{
    if (!data->input.raw_line)
		exit_builtin(data);
}

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	*data = (t_data){0};
	data->input = (t_input){0};
	data->envp = envp;
	data->argc = argc;
	data->argv = argv;
	data->status = -1;
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

void	free_environment(t_data *data)
{
	t_environment	*tmp;

	while (data->env)
	{
		free(data->env->variable);
		free(data->env->value);
		tmp = data->env;
		data->env = data->env->next;
		free(tmp);
	}
}

void	free_tokens(t_data *data)
{
	t_tokens	*tmp;

	while (data->input.tokens)
	{
		free(data->input.tokens->token);
		tmp = data->input.tokens;
		data->input.tokens = data->input.tokens->next;
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	int			i;

	free(data->prompt);
	free(data->input.raw_line);
	free(data->history);
	free_tokens(data);
	free_environment(data);
	i = -1;
	if (data->input.command)
	{
		while (data->input.command[++i].cmd)
			free(data->input.command[i].cmd);
		free(data->input.command);
	}
	free_mtrx(data->paths);
	free_mtrx(data->envp_cpy);
	i = data->status;
	init_data(data, data->argc, data->argv, data->envp);
	data->status = i;
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
	clear_history();
	exit(data.status);
}
