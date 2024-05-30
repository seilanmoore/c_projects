/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:50:58 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/30 17:24:29 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"

# include <fcntl.h>		//open
# include <unistd.h>	//close, read, write, access, dup, dup2, execve, pipe
# include <stdlib.h>	//malloc, free
# include <stdio.h>		//perror
# include <errno.h>		//errno
# include <string.h>	//strerror
# include <sys/wait.h>	//wait, waitpid

# define ERROR -1
# define ARGC 5
# define OPENF "open: couldn't open file"
# define CLOSEF "close: couldn't close file"
# define PIPEF "pipe: couldn't create pipe"
# define ALLOCF "couldn't allocate memory"
# define PATHF "couldn't find the command path"
# define FORKF "couldn't clone the process"
# define DUPF "couldn't duplicate the file descriptor"
# define EXECF "couldn't execute the command"

typedef struct s_data
{
	char	**argv;
	char	**envp;
	int		fd_in;
	int		fd_out;
	int		pipedes[2];
	int		pid;
	char	**cmd1;
	char	**cmd2;
	char	*cmd1p;
	char	*cmd2p;
	char	**paths;
}	t_data;

//MAIN
void	init(t_data *data, char **argv, char **envp);
void	get_path(t_data *data);

//UTILS
void	ft_error(t_data *data, char *message, char *sys_error);
void	cleanup(t_data *data);

#endif