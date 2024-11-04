/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:58:17 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/04 11:29:49 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/types.h>

static int	builtin_out(t_data *data, t_cmd *cmd, int fork)
{
	int	status;

	status = 0;
	if (!ft_strcmp(cmd->cmd, "exit"))
		status = exit_builtin(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "echo"))
		status = echo_builtin(cmd);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		status = cd_builtin(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		status = pwd_builtin(data);
	else if (!ft_strcmp(cmd->cmd, "export"))
		status = export_builtin(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		status = unset_builtin(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "env"))
		status = env_builtin(data);
	if (fork)
		exit (status);
	return (status);
}

static int	builtin_redir(t_data *data, t_cmd *cmd)
{
	int			exit_code;
	int			stdout_fd;

	stdout_fd = -1;
	if (data->fd[0] != -1)
	{
		close(data->fd[0]);
		data->fd[0] = -1;
	}
	if (data->heredoc)
	{
		ft_putstr_fd("Escribe en heredoc\n", 2);
		write_heredoc(data);
	}
	if (data->fd[1] != -1)
	{
		stdout_fd = dup(STDOUT_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
		data->fd[1] = -1;
	}
	exit_code = builtin_out(data, cmd, 0);
	if (stdout_fd != -1)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdout_fd);
	}
	return (exit_code);
}

static void	cmd_out(t_data *data, t_cmd *command)
{
	char	*path;
	char	**args;

	path = command->cmd;
	args = command->args;
	if (!path)
		exit(1);
	ft_putstr_fd("CMD path: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd("", 2);
	ft_putstr_fd("CMD args: ", 2);
	print_array(args);
	ft_putendl_fd("", 2);
	if (execve(path, args, data->envp) == -1)
	{
		if (!stat(path, &(data->stat)) && S_ISDIR(data->stat.st_mode))
		{
			ft_putstr_fd(MS, 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": " IS_DIR, 2);
		}
		else
			cmd_error(command->cmd, errno, 1);
		exit(errno);
	}
}

static int	exe_cmd(t_data *data, pid_t *pid)
{
	t_token	*cmd;
	int		exit_var;

	cmd = data->input.tokens;
	data->input.tokens = data->input.tokens->next;
	exit_var = open_files(data);
	if (exit_var)
		return (exit_var);
	/* ft_putstr_fd("-> exit_var despues de primer open_files: ", 2);
	ft_putnbr_fd(exit_var, 2);
	ft_putendl_fd("", 2); */
	if (cmd->cmd->builtin && data->n_pipe == 0)
	{
		// ft_putstr_fd("-> entramos en builtin_redir\n", 2);
		exit_var = builtin_redir(data, cmd->cmd);
	}
	else
	{
		if (data->r_pipe[0] != -1)
		{
			if (!(data->heredoc) && data->fd[0] == -1)
			{
				if (data->l_pipe[0] != -1)
					close(data->l_pipe[0]);
				if (data->l_pipe[1] != -1)
					close(data->l_pipe[1]);
				if (pipe(data->l_pipe) == -1)
					return (1);
				dup2(data->r_pipe[0], data->l_pipe[0]);
				dup2(data->r_pipe[1], data->l_pipe[1]);
			}
			if (data->r_pipe[0] != -1)
				close(data->r_pipe[0]);
			if (data->r_pipe[1] != -1)
				close(data->r_pipe[1]);
			data->r_pipe[0] = -1;
			data->r_pipe[1] = -1;
		}
		if (data->heredoc)
			write_heredoc(data);
		if (data->input.tokens)
		{
			if (data->fd[1] == -1 && data->input.tokens->prev && \
			data->input.tokens->prev->type == PIPE && \
			pipe(data->r_pipe) == -1)
				return (1);
		}
		*pid = fork();
		g_signal = *pid;
		if (*pid == -1)
			return (1);
		if (*pid == 0)
		{
			if (data->fd[0] != -1)
			{
				dup2(data->fd[0], STDIN_FILENO);
				close(data->fd[0]);
			}
			else if (data->l_pipe[0] != -1)
			{
				close(data->l_pipe[1]);
				dup2(data->l_pipe[0], STDIN_FILENO);
				close(data->l_pipe[0]);
			}
			if (data->fd[1] != -1)
			{
				dup2(data->fd[1], STDOUT_FILENO);
				close(data->fd[1]);
			}
			else if (data->r_pipe[1] != -1)
			{
				close(data->r_pipe[0]);
				dup2(data->r_pipe[1], STDOUT_FILENO);
				close(data->r_pipe[1]);
			}
			if (cmd->cmd->builtin)
				exit_var = builtin_out(data, cmd->cmd, 1);
			else
				cmd_out(data, cmd->cmd);
		}
		else
		{
			if (data->l_pipe[0] != -1)
				close(data->l_pipe[0]);
			if (data->l_pipe[1] != -1)
				close(data->l_pipe[1]);
			data->l_pipe[0] = -1;
			data->l_pipe[1] = -1;
			if (data->fd[0] != -1)
				close(data->fd[0]);
			if (data->fd[1] != -1)
				close(data->fd[1]);
			data->fd[0] = -1;
			data->fd[1] = -1;
		}
		waitpid(*pid, &data->status, 0);
		/* if (WIFEXITED(data->status))
		{
			exit_var = cmd_error(cmd->token,
					WEXITSTATUS(data->status), 0);
		} */
	}
	return (exit_var);
}

int	execute(t_data *data)
{
	t_token	*head;
	pid_t	*pid;
	int		i;
	int		exit_var;

	head = data->input.tokens;
	pid = ft_calloc(data->n_cmd, sizeof(pid_t));
	if (!pid)
		return (0);
	i = -1;
	while (data->input.tokens && !g_signal)
	{
		if (is_redir(data->input.tokens->type))
			exit_var = open_files(data);
		else if (data->input.tokens->type == CMD)
			exit_var = exe_cmd(data, &(pid[++i]));
	}
	if (WIFEXITED(data->status) && !g_signal)
	{
		exit_var = cmd_error(NULL, WEXITSTATUS(data->status), 0);
	}
	else if (g_signal)
		exit_var = 130;
	free(pid);
	data->input.tokens = head;
	return (exit_var);
}
