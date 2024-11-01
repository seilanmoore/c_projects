/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:34 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/01 18:00:38 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>

static void	upd_shlvl(t_data *data)
{
	t_env	*shlvl;
	int		lvl;

	shlvl = get_env_var(data->env, "SHLVL");
	if (shlvl && shlvl->value)
	{
		lvl = ft_atoi(shlvl->value);
		free(shlvl->value);
		shlvl->value = ft_itoa(lvl + 1);
		upd_env(data);
	}
}

int	count_vars(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		;
	return (i);
}

void	copy_envp(t_data *data, char **envp)
{
	int	i;

	if (!envp)
		return ;
	data->envp = ft_calloc(count_vars(envp) + 1, sizeof(char *));
	if (!data->envp)
		return ;
	i = -1;
	while (envp[++i])
		data->envp[i] = ft_strdup(envp[i]);
}

pid_t	ft_get_pid(void)
{
	int		fd;
	int		pid;
	char	*tmp;

	fd = open("/proc/self/stat", O_RDONLY);
	tmp = get_next_line(fd);
	pid = ft_atoi(tmp);
	free(tmp);
	close(fd);
	return (pid);
}

void	init_data(t_data *data, char **envp)
{
	*data = (t_data){0};
	data->input = (t_input){0};
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->l_pipe[0] = -1;
	data->l_pipe[1] = -1;
	data->r_pipe[0] = -1;
	data->r_pipe[1] = -1;
	data->pid = ft_get_pid();
	data->process = ft_itoa(data->pid);
	data->prev_exit_code = ft_itoa(0);
	copy_envp(data, envp);
	envp_to_lst(data);
	upd_shlvl(data);
}
