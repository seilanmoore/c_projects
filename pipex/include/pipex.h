/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:50:58 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/23 20:05:37 by smoore-a         ###   ########.fr       */
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

#endif