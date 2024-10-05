/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:58:17 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/05 15:22:08 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

static	t_token	*get_token(t_token *tokens, char *token)
{
	t_token *tmp;
	int		tmp_len;

	tmp = tokens;
	while (tmp)
	{
		tmp_len = ft_strlen(tmp->token);
		if (!ft_strncmp(tmp->token, token, tmp_len))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	builtin_out(t_data *data)
{
	char	*cmd;
	int		len;

	cmd = data->input.command->cmd;
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
		return (echo_builtin(data, get_token(data->input.tokens, "echo")));
	else if (!ft_strncmp(cmd, "cd", len))
		return (cd_builtin(data, get_token(data->input.tokens, "cd")));
	else if (!ft_strncmp(cmd, "pwd", len))
		return (pwd_builtin(data));
	else if (!ft_strncmp(cmd, "export", len))
		return (export_builtin(data));
	else if (!ft_strncmp(cmd, "unset", len))
		return (unset_builtin(data));
	else if (!ft_strncmp(cmd, "env", len))
		return (env_builtin(data));
	return (0);
}

static void	cmd_out(t_data *data)
{
	char	*path;
	char	**args;

	if (data->input.command->builtin)
		builtin_out(data);
	else
	{
		path = data->input.command->cmd;
		args = data->input.command->args;
		if (execve(path, args, data->envp_cpy) == -1)
			exit(127);
	}
}

static t_token	*get_redirecction(t_token *token)
{
	t_token	*redir;

	redir = token;
	while (redir)
	{
		if (redir->type != CMD && redir->type != OPTION && \
		redir->type != ARG && redir->type != FILE && \
		redir->type != VARIABLE && redir->type != VALUE && \
		redir->type != L_VARIABLE && redir->type != L_VALUE)
			return (redir);
		redir = redir->next;
	}
	return (NULL);
}

static void	create_child(t_data *data, t_token *redir, pid_t *pid, int i)
{
	//t_token *next_redir;

	(void)redir;
	if (i < data->n_pipe)
	{
		if (pipe(data->pipes[i].fd) == -1)
			return ;
	}
	*pid = fork();
	if (*pid == -1)
		return ;
	if (*pid == 0)
	{
		/* if (redir)
		{
			next_redir = get_redirecction(redir);
			if (redir->type == LEFT)
			{
				if (next_redir)
				{
					if (next_redir->type == PIPE)
						infile_cmd_pipe();
					else if (next_redir->type == RIGHT || next_redir->type == RIGHTT)
						infile_cmd_outfile()
				}
				else
					infile_cmd_out();
			}
			else if (redir->type == PIPE)
			{
				if (next_redir)
				{
					if (next_redir->type == PIPE)
						pipe_cmd_pipe();
					else if (next_redir->type == RIGHT || next_redir->type == RIGHTT)
						pipe_cmd_outfile()
				}
				else
					pipe_cmd_out();
			}
			else if (redir->type == RIGHT || \
			redir->type == RIGHTT)
				cmd_outfile();
		} */
		cmd_out(data);
	}
}

void	execute(t_data *data)
{
	t_cmd	*cmd_head;
	t_token	*redir;
	pid_t	*pid;
	int		i;

	if (!data->n_pipe && !ft_strncmp(data->input.command->cmd, "exit", ft_strlen(data->input.command->cmd)))
		exit_builtin(data);
	if (!data->n_pipe && data->input.command->builtin)
	{
		data->exit_code = builtin_out(data);
		return ;
	}
	pid = ft_calloc(data->n_cmd, sizeof(pid_t));
	if (!pid)
		return ;
	data->pipes = ft_calloc(data->n_pipe, sizeof(t_pipe));
	i = -1;
	cmd_head = data->input.command;
	redir = get_redirecction(data->input.tokens);
	while (++i < data->n_cmd)
	{
		create_child(data, redir, &(pid[i]), i);
		redir = get_redirecction(redir);
		data->input.command = data->input.command->next;
		waitpid(pid[i], &data->status, 0);
	}
	data->input.command = cmd_head;
	if (WIFEXITED(data->status))
		data->exit_code = WEXITSTATUS(data->status);
	free(data->pipes);
	free(pid);
}
