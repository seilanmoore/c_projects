/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:44 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/19 10:01:31 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>

// ANSI color codes
# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[34m"
# define WHITE	"\x1b[0m"

# define HISTORY_FILE ".history"

# define NL "\n"
# define MS "minishell: "
# define EMPTY_PATH "PATH variable is empty"
# define NO_PATH "PATH variable not found"
# define NOT_FOUND "command not found"
# define ERROR "error "

# define CMD 100	// cmd
# define OPTION 101	// cmd option
# define F_NAME 102	// file_name
# define PIPE 103 	// |
# define LEFT 104 	// <
# define RIGHT 105 	// >
# define LEFTT 106 	// <<
# define RIGHTT 107 // >>

typedef struct s_command
{
	char	*cmd;
	char	**opt;
}	t_command;

typedef struct s_tokens
{
	char	*token;
	int		type;
}	t_tokens;

typedef struct s_input
{
	char		*raw_line;
	char		*file_name;
	t_tokens	*tokens;
	t_command	*command;
}	t_input;

typedef struct	s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**paths;
	char	*user;
	char	*cwd;
	char	*prompt;
	int		n_cmd;
	int		n_token;
	int		exit_code;
	int		status;
	t_input	input;

}	t_data;


void	free_mtrx(char **mtrx);
void	parse(t_data *data);
void	get_env_paths(t_data *data);
void	exit_builtin(t_data *data);

#endif
