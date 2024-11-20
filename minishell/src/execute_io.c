/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:58:17 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/12 15:13:21 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>
#include <sys/types.h>

static int	wait_children(t_data *data, pid_t *pid)
{
	int	i;

	i = -1;
	while (++i < data->n_cmd)
		waitpid(pid[i], &data->status, 0);
	if (!WIFEXITED(data->status) && !g_signal)
		return (130);
	else if (!WIFEXITED(data->status) && g_signal)
	{
		ft_putendl_fd("Quit (core dumped)", 2);
		return (131);
	}
	else if (WIFEXITED(data->status))
		return (WEXITSTATUS(data->status));
	else
		return (0);
}

static int	child_exe(t_data *data, pid_t *pid, t_token *cmd)
{
	int	fail;

	fail = 0;
	g_signal = *pid;
	if (*pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		fail = handle_io(data);
		if (cmd->cmd->builtin && !fail)
			builtin_out(data, cmd->cmd, 1);
		else if (!fail)
			cmd_out(data, cmd->cmd);
		exit (fail);
	}
	close_parent_files(data);
	return (0);
}

/* static int	child_exe(t_data *data, pid_t *pid, t_token *cmd)
{
	int	fail;

	fail = 0;
	g_signal = *pid;
	if (*pid == 0)
	{
		fail = handle_io(data);
		if (cmd->cmd->builtin && !fail)
			builtin_out(data, cmd->cmd, 1);
		else if (!fail)
			cmd_out(data, cmd->cmd);
		exit (fail);
	}
	close_parent_files(data);
	waitpid(*pid, &data->status, 0);
	if (!WIFEXITED(data->status))
		return (130);
	else if (WIFEXITED(data->status))
		return (WEXITSTATUS(data->status));
	return (0);
} */

static int	cmd_exe(t_data *data, pid_t *pid, t_token *cmd)
{
	if (cmd->cmd->builtin && data->n_pipe == 0)
		return (builtin_redir(data, cmd->cmd));
	else
	{
		if (change_pipe(data))
			return (1);
		if (open_r_pipe(data))
			return (1);
		*pid = fork();
		if (*pid == -1)
			return (1);
		return (child_exe(data, pid, cmd));
	}
}

static int	cmd_io(t_data *data, pid_t *pid)
{
	t_token	*cmd;
	int		exit_var;

	exit_var = 0;
	cmd = data->input.tokens;
	data->last_cmd = cmd;
	data->input.tokens = data->input.tokens->next;
	exit_var = open_files(data);
	if (exit_var)
	{
		if (open_r_pipe(data) == 1)
			return (1);
		return (exit_var);
	}
	return (cmd_exe(data, pid, cmd));
}
//After while loop
//if (WIFEXITED(data->status) &&
//WEXITSTATUS(data->status)) //&& exit_var != 1 && exit_var != 130)
//exit_var = cmd_error(data, WEXITSTATUS(data->status), 0);

int	execute(t_data *data)
{
	t_token	*head;
	pid_t	*pid;
	int		i;
	int		exit_var;

	if (!data->n_cmd)
		return (data->exit_code);
	head = data->input.tokens;
	pid = ft_calloc(data->n_cmd, sizeof(pid_t));
	if (!pid)
		return (0);
	exit_var = -1;
	i = -1;
	while (data->input.tokens && exit_var != 130)
	{
		if (is_redir(data->input.tokens->type))
			exit_var = open_files(data);
		else if (data->input.tokens->type == CMD)
			exit_var = cmd_io(data, &(pid[++i]));
	}
	if ((!data->last_cmd->cmd->builtin || data->n_pipe) && exit_var != 1)
		exit_var = wait_children(data, pid);
	free(pid);
	data->input.tokens = head;
	return (exit_var);
}
