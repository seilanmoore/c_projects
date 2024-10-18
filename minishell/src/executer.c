/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:58:17 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/18 14:25:41 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_token	*get_redirecction(t_token *token)
{
	t_token	*redir;

	redir = token;
	if (redir)
		redir = redir->next;
	while (redir)
	{
		if (redir->type == PIPE || \
		redir->type == LEFT || redir->type == LEFTT || \
		redir->type == RIGHT || redir->type == RIGHTT)
			return (redir);
		redir = redir->next;
	}
	return (NULL);
}

static void	cmd_not_found(t_data *data, char *cmd)
{
	ft_putstr_fd(MS, 2);
	ft_putstr_fd(cmd, 2);
	print_msg(data, ": " NOT_FOUND, 127);
}

static	t_token	*get_token(t_token *tokens, char *token)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (!ft_strcmp(tmp->token, token))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	builtin_out(t_data *data)
{
	char	*cmd;

	cmd = data->input.command->cmd;
	if (!ft_strcmp(cmd, "exit"))
		return (exit_builtin(data));
	else if (!ft_strcmp(cmd, "echo"))
		return (echo_builtin(data, get_token(data->input.tokens, "echo")));
	else if (!ft_strcmp(cmd, "cd"))
		return (cd_builtin(data, get_token(data->input.tokens, "cd")));
	else if (!ft_strcmp(cmd, "pwd"))
		return (pwd_builtin(data));
	else if (!ft_strcmp(cmd, "export"))
		return (export_builtin(data, data->input.command));
	else if (!ft_strcmp(cmd, "unset"))
		return (unset_builtin(data, data->input.command));
	else if (!ft_strcmp(cmd, "env"))
		return (env_builtin(data));
	return (0);
}

static int	builtin_redir(t_data *data)
{
	t_token		*redir;
	int			fd[2];
	int			exit_code;
	int			stdout_backup;

	fd[0] = -1;
	fd[1] = -1;
	redir = get_redirecction(data->input.tokens);
	while (redir)
	{
		if (redir && redir->type == LEFT && redir->next)
		{
			fd[0] = open(redir->next->token, O_RDONLY);
			if (fd[0] == -1 && handle_errno(redir->next->token) == 1)
				return (1);
		}
		else if (redir && redir->type == RIGHT && redir->next)
		{
			fd[1] = open(redir->next->token, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd[1] == -1 && handle_errno(redir->next->token) == 1)
				return (1);
		}
		else if (redir && redir->type == RIGHTT && redir->next)
		{
			fd[1] = open(redir->next->token, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fd[1] == -1 && handle_errno(redir->next->token) == 1)
				return (1);
		}
		redir = get_redirecction(redir);
	}
	if (fd[1] > 2)
	{
		stdout_backup = dup(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	exit_code = builtin_out(data);
	if (fd[1] > 2)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
	while (fd[1] > 2)
		close(fd[1]--);
	return (exit_code);
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
		if (!path)
			exit(1);
		if (execve(path, args, data->envp) == -1)
		{
			cmd_not_found(data, data->input.command->cmd);
			exit(127);
		}
	}
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

int	execute(t_data *data)
{
	t_cmd	*cmd_head;
	t_token	*redir;
	pid_t	*pid;
	int		i;
	int		exit_var;

	exit_var = 0;
	//open_files(data);
	if (!data->input.command)
		return (exit_var);
	if (!data->n_pipe && data->input.command->builtin)
		return (builtin_redir(data));
	pid = ft_calloc(data->n_cmd, sizeof(pid_t));
	if (!pid)
		return (0);
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
		exit_var = WEXITSTATUS(data->status);
	free(data->pipes);
	free(pid);
	return (exit_var);
}
