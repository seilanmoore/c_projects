/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:58:17 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/09 19:28:10 by smoore-a         ###   ########.fr       */
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
		if (redir->type != CMD && redir->type != OPTION && \
		redir->type != ARG && redir->type != FILE && \
		redir->type != VARIABLE && redir->type != VALUE && \
		redir->type != L_VARIABLE && redir->type != L_VALUE)
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

static int	is_dir_check(char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) == -1)
		return (0);
	if (stat(path, &path_stat))
		return (1);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": " IS_DIR, 2);
		return (1);
	}
	return (0);
}

static int	check_left_path(char *path)
{
	if (dir_f_check(path) == 1)
		return (1);
	if (is_dir_check(path) == 1)
		return (1);
	if (dir_r_check(path) == 1)
		return (1);
	if (path_r_check(path) == 1)
		return (1);
	return (0);
}

static int	check_right_path(char *path)
{
	if (dir_f_check(path) == 1)
		return (1);
	if (is_dir_check(path) == 1)
		return (1);
	if (dir_w_check(path) == 1)
		return (1);
	if (path_w_check(path) == 1)
		return (1);
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
			/* if (check_left_path(redir->next->token) == 1)
				;//	return (1); */
			fd[0] = open(redir->next->token, O_RDONLY);
			if (fd[0] == -1)
			{
				if (handle_errno(redir->next->token) == 1)
					return (1);
				if (access(redir->next->token, R_OK) == -1)
				{
					ft_putstr_fd(MS, 2);
					ft_putstr_fd(redir->next->token, 2);
					ft_putendl_fd(": " PERMIT, 2);
					return (1);
				}
			}
		}
		else if (redir && redir->type == RIGHT && redir->next)
		{
			/* if (check_right_path(redir->next->token) == 1)
				return (1); */
			fd[1] = open(redir->next->token, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd[1] == -1)
			{
				if (handle_errno(redir->next->token) == 1)
					return (1);
				if (access(redir->next->token, W_OK) == -1)
				{
					ft_putstr_fd(MS, 2);
					ft_putstr_fd(redir->next->token, 2);
					ft_putendl_fd(": " PERMIT, 2);
					return (1);
				}
			}
		}
		else if (redir && redir->type == RIGHTT && redir->next)
		{
			/* if (check_right_path(redir->next->token) == 1)
				return (1); */
			fd[1] = open(redir->next->token, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fd[1] == -1)
			{
				if (handle_errno(redir->next->token) == 1)
					return (1);
				if (access(redir->next->token, W_OK) == -1)
				{
					ft_putstr_fd(MS, 2);
					ft_putstr_fd(redir->next->token, 2);
					ft_putendl_fd(": " PERMIT, 2);
					return (1);
				}
			}
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
		if (execve(path, args, data->envp_cpy) == -1)
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
		data->exit_code = builtin_redir(data);
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
