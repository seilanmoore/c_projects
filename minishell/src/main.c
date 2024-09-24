/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/24 12:05:17 by smoore-a         ###   ########.fr       */
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

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	*data = (t_data){0};
	data->env = (t_environment *){0};
	data->input = (t_input){0};
	data->envp = envp;
	data->argc = argc;
	data->argv = argv;
	data->status = -1;
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	free_environment(t_data *data)
{
	t_environment	*tmp;

	while (data->env)
	{
		free(data->env->variable);
		data->env->variable = NULL;
		free(data->env->value);
		data->env->value = NULL;
		tmp = data->env;
		data->env = data->env->next;
		free(tmp);
	}
	free_array(data->envp_cpy);
	data->envp_cpy = NULL;
}

void	free_tokens(t_data *data)
{
	t_tokens	*tmp;

	while (data->input.tokens)
	{
		free(data->input.tokens->token);
		data->input.tokens->token = NULL;
		tmp = data->input.tokens;
		data->input.tokens = data->input.tokens->next;
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	int				i;
	t_environment	*env_head;
	char			**env_ptr;

	env_head = data->env;
	env_ptr = data->envp_cpy;
	free(data->prompt);
	free(data->input.raw_line);
	free(data->history);
	free_tokens(data);
	i = -1;
	if (data->input.command)
	{
		while (data->input.command[++i].cmd)
			free(data->input.command[i].cmd);
		free(data->input.command);
	}
	free_array(data->paths);
	i = data->status;
	init_data(data, data->argc, data->argv, data->envp);
	data->env = env_head;
	data->envp_cpy = env_ptr;
	data->status = i;
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
