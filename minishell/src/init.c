/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:34 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/26 14:29:25 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>

pid_t	ft_get_pid(void)
{
	int		fd;
	int		pid;
	char	*tmp;

	fd = open("/proc/self/stat", O_RDONLY);
	tmp = get_next_line(fd);
	pid = ft_atoi(tmp);
	free(tmp);
	if (fd)
		close(fd);
	return (pid);
}

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	*data = (t_data){0};
	data->env = (t_environment *){0};
	data->local = (t_l_variable *){0};
	data->input = (t_input){0};
	data->envp = envp;
	data->argc = argc;
	data->argv = argv;
	data->status = -1;
	data->exit_code = -1;
	data->pid = ft_get_pid();
	data->process = ft_itoa(data->pid);
}
