/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:44 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/25 11:16:59 by smoore-a         ###   ########.fr       */
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

# define CMD 100		// cmd
# define OPTION 101		// cmd option
# define ARG 102		// argument
# define PIPE 103 		// |
# define LEFT 104 		// <
# define RIGHT 105 		// >
# define LEFTT 106 		// <<
# define RIGHTT 107 	// >>
# define FILE 108		// file
# define HERE 109 		// heredoc
# define VARIABLE 110 	// variable=value
# define VALUE 111 		// variable=value
# define L_VARIABLE 112 // local variable=value
# define L_VALUE 113 	// local variable=value
# define S_QUOTE 114 	// ''
# define D_QUOTE 115 	// ""
# define NO_QUOTE 116

typedef struct s_l_variable
{
	char				*variable;
	char				*value;
	struct s_l_variable	*next;
}	t_l_variable;

typedef struct s_command
{
	char	*cmd;
	char	**opt;
}	t_command;

typedef struct s_tokens
{
	char				*token;
	int					type;
	struct s_tokens		*prev;
	struct s_tokens		*next;
}	t_tokens;

typedef struct s_input
{
	char		*raw_line;
	char		*file_name;
	t_tokens	*tokens;
	t_command	*command;
}	t_input;

typedef struct s_var
{
	char	*aux;
	char	*aux1;
	int		i;

}	t_var;

typedef struct s_environment
{
	char					*variable;
	char					*value;
	//struct	s_environment	*prev;
	struct s_environment	*next;
}	t_environment;

typedef struct s_data
{
	int				argc;
	char			**argv;
	char			**envp;
	char			**envp_cpy;
	char			**paths;
	char			*user;
	char			*cwd;
	char			*prompt;
	char			*history;
	int				n_cmd;
	int				n_token;
	int				status;
	t_l_variable	*local;
	t_environment	*env;
	t_input			input;
}	t_data;

// init
void			init_data(t_data *data, int argc, char **argv, char **envp);

// free_func
void			free_tokens(t_data *data);
void			free_local(t_data *data);
void			free_environment(t_data *data);
void			free_array(char **array);
void			free_data(t_data *data);

// local
void			print_locals(t_data *data);
void			add_l_variables(t_data *data);

//parser
void			parser(t_data *data);
void			get_env_paths(t_data *data);

//builtin
void			exit_builtin(t_data *data);
void			env_builtin(t_data *data);
void			export_builtin(t_data	*data);

t_tokens		*new_token(void *token, int type);
int				lst_size(t_tokens *lst);

void			add_front_token(t_tokens **lst, t_tokens *node);
t_tokens		*last_token(t_tokens *lst);
void			add_back_token(t_tokens **lst, t_tokens *node);

t_environment	*new_variable(void *variable, char *value);
t_environment	*last_variable(t_environment *lst);
void			add_back_variable(t_environment **lst, t_environment *node);
void			add_front_variable(t_environment **lst, t_environment *node);
int				env_size(t_environment *lst);
t_environment	*get_env_var(t_environment *env, char *variable);

void			parse_environment(t_data *data);
void			envp_to_array(t_data *data);
void			update_env(t_data	*data);


void			print_array(char	**array);

#endif
