/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:44 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/21 18:52:40 by smoore-a         ###   ########.fr       */
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
# define ARG 102	// argument
# define FILE 109	// file
# define PIPE 103 	// |
# define LEFT 104 	// <
# define RIGHT 105 	// >
# define LEFTT 106 	// <<
# define RIGHTT 107 // >>
# define HERE 110 // here_doc
# define QUOTE 108 // "" || ''

typedef struct s_command
{
	char	*cmd;
	char	**opt;
}	t_command;

typedef struct s_tokens
{
	char				*token;
	int					type;
	struct	s_tokens	*prev;
	struct	s_tokens	*next;
}	t_tokens;

typedef struct s_input
{
	char		*raw_line;
	char		*file_name;
	t_tokens	*tokens;
	t_command	*command;
}	t_input;

typedef struct	s_var
{
	char	*aux;
	char	*aux1;
	int		i;

}	t_var;

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
	int		status;
	t_input	input;

}	t_data;


void		free_mtrx(char **mtrx);
void		parser(t_data *data);
void		get_env_paths(t_data *data);
void		exit_builtin(t_data *data);
void		free_data(t_data *data);

t_tokens	*new_token(void *token, int type);
int			lst_size(t_tokens *lst);


void		add_front_token(t_tokens **lst, t_tokens *node);
t_tokens	*last_token(t_tokens *lst);
void		add_back_token(t_tokens **lst, t_tokens *node);
#endif
