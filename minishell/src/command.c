/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:39:54 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/17 12:44:43 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

static int	is_built(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

static int	count_args(t_token *token)
{
	t_token	*tmp;
	int		n_args;

	n_args = 1;
	tmp = token->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OPTION || tmp->type == ARG)
			n_args++;
		tmp = tmp->next;
	}
	return (n_args);
}

static char	*put_quotes(t_token *token)
{
	char	*arg;
	char	*tmp;

	arg = NULL;
	if (token->quote == S_QUOTE)
	{
		tmp = ft_strjoin("\'", token->token);
		arg = ft_strjoin(tmp, "\'");
		free(tmp);
	}
	else if (token->quote == D_QUOTE)
	{
		tmp = ft_strjoin("\"", token->token);
		arg = ft_strjoin(tmp, "\"");
		free(tmp);
	}
	return (arg);
}

static char	**extract_args(t_token *token, int built)
{
	char	**args;
	int		i;

	args = ft_calloc(count_args(token) + 1, sizeof(char *));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(token->token);
	token = token->next;
	i = 1;
	while (token && token->type != PIPE)
	{
		if (token->type == OPTION || token->type == ARG)
		{
			if (!built && (token->quote == S_QUOTE || token->quote == D_QUOTE))
				args[i] = put_quotes(token);
			else
				args[i] = ft_strdup(token->token);
			if (!args[i])
				return (args);
			i++;
		}
		token = token->next;
	}
	return (args);
}

void	parse_cmd_opt(t_data *data)
{
	t_token	*tmp;
	char	**args;
	int		built;

	tmp = data->input.tokens;
	while (tmp)
	{
		if (tmp->token && tmp->type == CMD)
		{
			built = is_built(tmp->token);
			args = extract_args(tmp, built);
			add_back_cmd(&(data->input.command),
				new_cmd(ft_strdup(tmp->token), args, built));
		}
		tmp = tmp->next;
	}
	print_cmd_array(data);
	assign_paths(data);
}
