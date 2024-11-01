/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:41:47 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/01 18:18:02 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>
#include <unistd.h>

static int	open_infile(t_data *data, t_token *token)
{
	char	*file;

	close(data->fd[0]);
	close(data->r_pipe[0]);
	close(data->r_pipe[1]);
	data->r_pipe[0] = -1;
	data->r_pipe[1] = -1;
	file = token->token;
	if (!stat(file, &(data->stat)) && S_ISDIR(data->stat.st_mode))
	{
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": " IS_DIR, 2);
		return (1);
	}
	data->fd[0] = open(file, O_RDONLY);
	if (data->fd[0] == -1)
		return (handle_errno(file), 1);
	data->heredoc = NULL;
	return (0);
}

static int	open_heredoc(t_data *data)
{
	close(data->r_pipe[0]);
	close(data->r_pipe[1]);
	data->r_pipe[0] = -1;
	data->r_pipe[1] = -1;
	close(data->fd[0]);
	data->fd[0] = -1;
	if (pipe(data->l_pipe) == -1)
		return (1);
	data->input.tokens = data->input.tokens->next;
	data->heredoc = data->input.tokens->token;
	return (0);
}

static int	trunc_file(t_data *data, t_token *token)
{
	char	*file;

	close(data->fd[1]);
	file = token->token;
	data->fd[1] = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->fd[1] == -1)
		return (handle_errno(file), 1);
	data->input.tokens = data->input.tokens->next;
	return (0);
}

static int	append_file(t_data *data, t_token *token)
{
	char	*file;

	close(data->fd[1]);
	file = token->token;
	data->fd[1] = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (data->fd[1] == -1)
		return (handle_errno(file), 1);
	data->input.tokens = data->input.tokens->next;
	return (0);
}

int	open_files(t_data *data)
{
	int	status;
	int	type;

	status = 0;
	type = CMD;
	if (data->input.tokens)
		type = data->input.tokens->type;
	while (data->input.tokens && type != CMD)
	{
		if (type == LEFT)
			status = open_infile(data, data->input.tokens->next);
		else if (type == LEFTT)
			status = open_heredoc(data);
		else if (type == RIGHT)
			status = trunc_file(data, data->input.tokens->next);
		else if (type == RIGHTT)
			status = append_file(data, data->input.tokens->next);
		data->input.tokens = data->input.tokens->next;
		if (data->input.tokens)
			type = data->input.tokens->type;
		if (status)
			return (1);
	}
	return (0);
}
