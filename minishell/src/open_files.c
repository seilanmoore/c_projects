/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:41:47 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/24 21:53:09 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	open_infile(t_data *data, t_token *token)
{
	char	*file;

	file = token->token;
	close_infiles(data);
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
	close_infiles(data);
	if (pipe(data->l_pipe) == -1)
		return (1);
	data->input.tokens = data->input.tokens->next;
	data->heredoc = data->input.tokens->token;
	if (write_heredoc(data) == 130)
		return (130);
	return (0);
}

static int	trunc_file(t_data *data, t_token *token)
{
	char	*file;

	if (data->fd[1] != -1)
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

	if (data->fd[1] != -1)
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

	status = 0;
	while (data->input.tokens && data->input.tokens->type != PIPE)
	{
		if (data->input.tokens->type == LEFT)
			status = open_infile(data, data->input.tokens->next);
		else if (data->input.tokens->type == LEFTT)
			status = open_heredoc(data);
		else if (data->input.tokens->type == RIGHT)
			status = trunc_file(data, data->input.tokens->next);
		else if (data->input.tokens->type == RIGHTT)
			status = append_file(data, data->input.tokens->next);
		data->input.tokens = data->input.tokens->next;
		if (status)
		{
			while (data->input.tokens && data->input.tokens->type != CMD)
				data->input.tokens = data->input.tokens->next;
			return (status);
		}
	}
	if (data->input.tokens)
		data->input.tokens = data->input.tokens->next;
	return (0);
}
