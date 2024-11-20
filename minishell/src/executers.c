/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:06:51 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/11 23:17:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_out(t_data *data, t_cmd *cmd, int fork)
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
	else if (!ft_strcmp(cmd->cmd, "history"))
		status = history_builtin();
	if (fork)
		exit (status);
	return (status);
}

int	builtin_redir(t_data *data, t_cmd *cmd)
{
	int	exit_code;
	int	stdout_fd;

	stdout_fd = -1;
	if (data->fd[0] != -1)
	{
		close(data->fd[0]);
		data->fd[0] = -1;
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

//Inside if cond.
//	cmd_error(data, errno, 1);

void	cmd_out(t_data *data, t_cmd *command)
{
	char	*path;
	char	**args;

	path = command->cmd;
	args = command->args;
	if (!path)
		exit(1);
	if (execve(path, args, data->envp) == -1)
		exit(execve_error(data, command));
}
