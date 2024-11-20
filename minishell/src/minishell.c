/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:28:08 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/12 16:48:43 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_eof(t_data *data)
{
	if (!data->input.raw_line)
		exit_builtin(data, NULL);
}

static char	*get_cwd(t_data *data, char *prompt)
{
	t_env	*pwd;
	char	*short_cwd;
	char	*tmp;

	if (!(data->cwd))
	{
		pwd = get_env_var(data->env, "PWD");
		if (pwd)
			data->cwd = ft_strdup(pwd->value);
	}
	short_cwd = cwd_compress(data);
	if (short_cwd)
	{
		tmp = ft_strjoin(prompt, short_cwd);
		free(short_cwd);
	}
	else
		tmp = ft_strjoin(prompt, data->cwd);
	return (tmp);
}

static char	*prompter(t_data *data)
{
	char	*prompt;
	char	*tmp;

	data->user = getenv("USER");
	tmp = ft_strjoin("[", data->user);
	prompt = ft_strjoin(tmp, ": ");
	free (tmp);
	data->cwd = getcwd(NULL, 0);
	tmp = get_cwd(data, prompt);
	free(prompt);
	data->prompt = ft_strjoin(tmp, "]$ ");
	free(tmp);
	return (data->prompt);
}

void	minishell(t_data *data)
{
	g_signal = 0;
	data->input.raw_line = readline(prompter(data));
	handle_eof(data);
	if (data->input.raw_line && ft_strlen(data->input.raw_line) > 0 \
	&& !g_signal)
	{
		data->history = ft_strtrim(data->input.raw_line, "\n");
		if (data->history && ft_strlen(data->history) > 0)
			add_history(data->history);
		save_history();
		parser(data);
		if (syntax_error(data))
			data->exit_code = 2;
		else
			data->exit_code = execute(data);
		free(data->prev_exit_code);
		data->prev_exit_code = ft_itoa(data->exit_code);
	}
	free_data(data);
}
