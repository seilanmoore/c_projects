/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:04:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/08 13:44:30 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../../libft/include/libft.h"

# include <fcntl.h>		//open
# include <unistd.h>	//close, read, write, access, dup, dup2, execve, pipe
# include <stdlib.h>	//malloc, free
# include <stdio.h>		//perror
# include <errno.h>		//errno
# include <string.h>	//strerror
# include <sys/wait.h>	//wait, waitpid

# define ERROR -1
# define ARGC 5
# define OPENF ": No such file or directory\n"
# define CLOSEF "close: couldn't close file"
# define PIPEF "pipe: couldn't create pipe"
# define ALLOCF "couldn't allocate memory"
# define PATHF ": command not found"
# define FORKF "couldn't clone the process"
# define DUPF "couldn't duplicate the file descriptor"
# define EXECF "couldn't execute the command"

typedef struct s_cmd
{
	char	**opt;
	char	*path;
}	t_cmd;

typedef struct s_file
{
	char	*name;
	int		fd;
}	t_file;

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	t_file	file[2];
	int		pipedes[2];
	pid_t	*pid;
	char	**paths;
	t_cmd	*cmd;
	int		exit_code;
}	t_data;

void	ft_error(t_data *data, char *message, char *sys_error);
void	cleanup(t_data *data);

void	init(t_data *data, int argc, char ***argv, char ***envp);


#endif

